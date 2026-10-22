#include "RebirthCookedTextureSkip.h"
#include "RebirthCookAssetManagerProxy.h"
#include "RebirthCookedCopies.h"
#include "RebirthSafeLoad.h"

#include "AssetRegistry/AssetData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "CoreGlobals.h"
#include "Engine/Engine.h"
#include "Engine/Texture.h"
#include "GameDelegates.h"
#include "Logging/LogMacros.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "Modules/ModuleManager.h"
#include "UObject/Class.h"
#include "UObject/NameTypes.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthCookedTextures, Log, All);

namespace
{
	bool GCookedTextureSkipInstalled = false;
	FCookModificationDelegate GCookedTextureSkipPrevious;
	FDelegateHandle GCookedTextureSkipAssetLoadedHandle;
	FDelegateHandle GCookedTextureSkipPreGCHandle;

	/** The proxy currently standing in for the asset manager, if any (rooted while it is). */
	TWeakObjectPtr<URebirthCookAssetManagerProxy> GCookedTextureSkipActiveProxy;

	bool CookedTextureSkipIsTextureClass(FName ClassName)
	{
		if (ClassName.IsNone())
		{
			return false;
		}
		const UClass* Class = FindObject<UClass>(ANY_PACKAGE, *ClassName.ToString());
		return Class != nullptr && Class->IsChildOf(UTexture::StaticClass());
	}

	/** Long package names of every texture package saved cooked (PKG_FilterEditorOnly), sorted. */
	TArray<FName> CookedTextureSkipFindPackages()
	{
		IAssetRegistry& Registry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();
		if (Registry.IsLoadingAssets())
		{
			Registry.SearchAllAssets(true);
		}

		TArray<FAssetData> Assets;
		Registry.GetAllAssets(Assets, true);

		TSet<FName> Packages;
		for (const FAssetData& Asset : Assets)
		{
			if ((Asset.PackageFlags & PKG_FilterEditorOnly) != 0 && !Packages.Contains(Asset.PackageName) && CookedTextureSkipIsTextureClass(Asset.AssetClass))
			{
				Packages.Add(Asset.PackageName);
			}
		}
		TArray<FName> Sorted = Packages.Array();
		Sorted.Sort(FNameLexicalLess());
		return Sorted;
	}

	/** The rebuilt RM_Surface's package (Tools\RebuiltSurface): editable in this project, never cooked; the game has its own. */
	const TCHAR* const CookedTextureSkipRebuiltSurface = TEXT("/Game/Renderer/Material/RM_Surface");

	/** Whether the package is in the project saved by the editor (the rebuilt RM_Surface), not cooked (the game's own). */
	bool CookedTextureSkipIsEditable(FName PackageName)
	{
		IAssetRegistry& Registry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();
		if (Registry.IsLoadingAssets())
		{
			Registry.SearchAllAssets(true);
		}
		TArray<FAssetData> Assets;
		Registry.GetAssetsByPackageName(PackageName, Assets, true);
		for (const FAssetData& Asset : Assets)
		{
			if ((Asset.PackageFlags & PKG_FilterEditorOnly) == 0)
			{
				return true;
			}
		}
		return false;
	}

	/** Puts the real asset manager back if the proxy is still standing in (ModifyCook normally does this itself). */
	void CookedTextureSkipRestore(const TCHAR* Reason)
	{
		URebirthCookAssetManagerProxy* Proxy = GCookedTextureSkipActiveProxy.Get();
		if (Proxy == nullptr)
		{
			return;
		}
		GCookedTextureSkipActiveProxy.Reset();
		if (GEngine != nullptr && GEngine->AssetManager == Proxy)
		{
			GEngine->AssetManager = Proxy->RealAssetManager;
			UE_LOG(LogRebirthCookedTextures, Warning, TEXT("The cook did not call ModifyCook after its modification delegate; restored the asset manager (%s). Cooked textures may not be left out of this cook."), Reason);
		}
		Proxy->RemoveFromRoot();
	}

	/** Runs inside UCookOnTheFlyServer::CollectFilesToCook, right before UAssetManager::Get().ModifyCook(...). */
	void CookedTextureSkipOnCookModification(TArray<FString>& ExtraPackagesToCook)
	{
		// Keep whatever was bound before this plugin loaded.
		GCookedTextureSkipPrevious.ExecuteIfBound(ExtraPackagesToCook);

		if (GCookedTextureSkipActiveProxy.IsValid())
		{
			return;
		}
		if (GEngine == nullptr || GEngine->AssetManager == nullptr)
		{
			UE_LOG(LogRebirthCookedTextures, Warning, TEXT("No asset manager: cooked textures in the project cannot be left out of this cook."));
			return;
		}

		TArray<FName> Packages;
		if (FParse::Param(FCommandLine::Get(), TEXT("RebirthCookCookedTextures")))
		{
			UE_LOG(LogRebirthCookedTextures, Display, TEXT("-RebirthCookCookedTextures: cooked textures are not left out of the cook."));
		}
		else
		{
			Packages = CookedTextureSkipFindPackages();
		}
		const int32 NumTextures = Packages.Num();
		if (!FParse::Param(FCommandLine::Get(), TEXT("RebirthCookCookedCopies")))
		{
			// Cooked copies of the game's blueprints and data assets: cooking them again would not give back the game's
			// files (RebirthCookedCopies.h); the game loads its own.
			const TArray<FName> Copies = RebirthCookedCopies::FindPackages();
			for (const FName& Copy : Copies)
			{
				Packages.AddUnique(Copy);
			}
			UE_LOG(LogRebirthCookedTextures, Display,
				TEXT("%d cooked blueprint and data asset copies of the game are left out of this cook (packages that use them keep their references; run with -RebirthCookCookedCopies to cook them)."),
				Packages.Num() - NumTextures);
		}
		const TArray<FName> SelfTests = RebirthCookedCopies::FindSelfTestPackages();
		for (const FName& Test : SelfTests)
		{
			Packages.AddUnique(Test);
		}
		if (SelfTests.Num() > 0)
		{
			UE_LOG(LogRebirthCookedTextures, Display, TEXT("%d self-test package(s) in /Game/RebirthDataObjectTests are left out of this cook."), SelfTests.Num());
		}
		// What this cook never writes may load with default values when its saved properties don't fit this project's
		// classes (Rebirth Safe Cooked Loading), instead of crashing the cook when an editable asset references it.
		RebirthSafeLoad::AddPackagesLeftOutOfCook(Packages);
		// The rebuilt RM_Surface is for the editor only: mods keep referencing RM_Surface and the game loads its own (a cooked
		// RM_Surface put back with restore_cooked_rm_surface.cmd cooks as before).
		const FName RebuiltSurface(CookedTextureSkipRebuiltSurface);
		if (!Packages.Contains(RebuiltSurface) && CookedTextureSkipIsEditable(RebuiltSurface))
		{
			Packages.Add(RebuiltSurface);
			UE_LOG(LogRebirthCookedTextures, Display, TEXT("The rebuilt RM_Surface (%s) is left out of this cook: the game has its own RM_Surface."), CookedTextureSkipRebuiltSurface);
		}
		if (Packages.Num() == 0)
		{
			UE_LOG(LogRebirthCookedTextures, Display, TEXT("No cooked textures, game copies or self-test assets found; nothing to leave out of this cook."));
			return;
		}

		FString Examples;
		for (int32 Index = 0; Index < Packages.Num(); ++Index)
		{
			UE_LOG(LogRebirthCookedTextures, Log, TEXT("Leaving already-cooked package out of the cook: %s"), *Packages[Index].ToString());
			if (Index < 5)
			{
				Examples += (Index == 0 ? FString() : FString(TEXT(", "))) + Packages[Index].ToString();
			}
		}

		URebirthCookAssetManagerProxy* Proxy = NewObject<URebirthCookAssetManagerProxy>(GetTransientPackage(), NAME_None, RF_Transient);
		Proxy->RealAssetManager = GEngine->AssetManager;
		Proxy->ExtraNeverCookPackages = MoveTemp(Packages);
		Proxy->AddToRoot();
		GCookedTextureSkipActiveProxy = Proxy;
		// The cooker calls UAssetManager::Get().ModifyCook(...) as soon as this delegate returns.
		GEngine->AssetManager = Proxy;

		UE_LOG(LogRebirthCookedTextures, Display,
			TEXT("%d already-cooked package(s) (%d texture(s)) are left out of this cook; the game has its own copies and packages that use them keep their references: %s%s"),
			Proxy->ExtraNeverCookPackages.Num(), NumTextures, *Examples, Proxy->ExtraNeverCookPackages.Num() > 5 ? TEXT(", ...") : TEXT(""));
	}

	void CookedTextureSkipOnAssetLoaded(UObject*)
	{
		if (GCookedTextureSkipActiveProxy.IsValid())
		{
			CookedTextureSkipRestore(TEXT("asset loaded"));
		}
	}

	void CookedTextureSkipOnPreGarbageCollect()
	{
		if (GCookedTextureSkipActiveProxy.IsValid())
		{
			CookedTextureSkipRestore(TEXT("garbage collection"));
		}
	}
}

void URebirthCookAssetManagerProxy::PostInitProperties()
{
	// UAssetManager::PostInitProperties binds FCoreUObjectDelegates::GetPrimaryAssetIdForObject, OnObjectSaved and the PIE
	// delegates to the manager being initialized. They must stay bound to the engine's real asset manager.
	UObject::PostInitProperties();
}

void URebirthCookAssetManagerProxy::ModifyCook(TArray<FName>& PackagesToCook, TArray<FName>& PackagesToNeverCook)
{
	UAssetManager* Real = RealAssetManager;
	if (GEngine != nullptr && GEngine->AssetManager == this)
	{
		GEngine->AssetManager = Real;
	}
	if (GCookedTextureSkipActiveProxy.Get() == this)
	{
		GCookedTextureSkipActiveProxy.Reset();
	}
	RemoveFromRoot();

	if (Real != nullptr && Real != this)
	{
		Real->ModifyCook(PackagesToCook, PackagesToNeverCook);
	}

	const int32 Before = PackagesToNeverCook.Num();
	for (const FName PackageName : ExtraNeverCookPackages)
	{
		PackagesToNeverCook.AddUnique(PackageName);
	}
	UE_LOG(LogRebirthCookedTextures, Display, TEXT("Added %d already-cooked package(s) to the cook's never-cook list."), PackagesToNeverCook.Num() - Before);
}

namespace RebirthCookedTextureSkip
{
	void Install()
	{
		if (!IsRunningCommandlet() || GCookedTextureSkipInstalled)
		{
			return;
		}
		FCookModificationDelegate& Delegate = FGameDelegates::Get().GetCookModificationDelegate();
		GCookedTextureSkipPrevious = Delegate;
		Delegate.BindStatic(&CookedTextureSkipOnCookModification);
		GCookedTextureSkipAssetLoadedHandle = FCoreUObjectDelegates::OnAssetLoaded.AddStatic(&CookedTextureSkipOnAssetLoaded);
		GCookedTextureSkipPreGCHandle = FCoreUObjectDelegates::GetPreGarbageCollectDelegate().AddStatic(&CookedTextureSkipOnPreGarbageCollect);
		GCookedTextureSkipInstalled = true;
	}

	void Uninstall()
	{
		if (!GCookedTextureSkipInstalled)
		{
			return;
		}
		CookedTextureSkipRestore(TEXT("module shutdown"));
		FGameDelegates::Get().GetCookModificationDelegate() = GCookedTextureSkipPrevious;
		GCookedTextureSkipPrevious.Unbind();
		FCoreUObjectDelegates::OnAssetLoaded.Remove(GCookedTextureSkipAssetLoadedHandle);
		FCoreUObjectDelegates::GetPreGarbageCollectDelegate().Remove(GCookedTextureSkipPreGCHandle);
		GCookedTextureSkipInstalled = false;
	}
}
