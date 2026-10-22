#include "RebirthCookedMaterialConversion.h"

#include "RebirthRecoveredSurfaces.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "Editor.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/IConsoleManager.h"
#include "HAL/PlatformFilemanager.h"
#include "Logging/LogMacros.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Misc/DateTime.h"
#include "Misc/FileHelper.h"
#include "Misc/MessageDialog.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"
#include "PackageTools.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "UObject/Linker.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthCookedConversion, Log, All);

namespace
{
	TUniquePtr<FAutoConsoleCommand> GConvertCommand;

	bool ConvertIsCookedPackage(const UObject* Object)
	{
		const UPackage* Package = Object ? Object->GetOutermost() : nullptr;
		return Package && (Package->bIsCookedForEditor || Package->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly));
	}

	bool ConvertHasOverrideFlags(const FMaterialInstanceBasePropertyOverrides& Overrides)
	{
		return Overrides.bOverride_OpacityMaskClipValue || Overrides.bOverride_BlendMode || Overrides.bOverride_ShadingModel ||
			Overrides.bOverride_DitheredLODTransition || Overrides.bOverride_CastDynamicShadowAsMasked || Overrides.bOverride_TwoSided;
	}

	/** The parent, static parameters and overrides the instance was loaded with (before any in-memory preview redirect). */
	void ConvertOriginalState(const UMaterialInstanceConstant* Instance, UMaterialInterface*& OutParent, FStaticParameterSet& OutStatic,
		FMaterialInstanceBasePropertyOverrides& OutOverrides)
	{
		OutParent = Instance->Parent;
		OutStatic = Instance->GetStaticParameters();
		OutOverrides = Instance->BasePropertyOverrides;
		RebirthRecoveredSurfaces::GetOriginalState(Instance, OutParent, OutStatic, OutOverrides);
	}

	bool ConvertCheck(UMaterialInstanceConstant* Instance, FString& OutFilename, FString& OutReason)
	{
		if (!IsValid(Instance) || Instance->HasAnyFlags(RF_ClassDefaultObject | RF_NeedLoad | RF_NeedPostLoad))
		{
			OutReason = TEXT("it is not fully loaded");
			return false;
		}
		if (!ConvertIsCookedPackage(Instance))
		{
			OutReason = TEXT("it is already an editable asset");
			return false;
		}
		if (Instance->GetOuter() != Instance->GetOutermost())
		{
			OutReason = TEXT("it is not the main asset of its package");
			return false;
		}
		FString Filename;
		if (!FPackageName::DoesPackageExist(Instance->GetOutermost()->GetName(), nullptr, &Filename))
		{
			OutReason = TEXT("its package file was not found");
			return false;
		}
		Filename = FPaths::ConvertRelativePathToFull(Filename);
		if (!FPaths::GetExtension(Filename).Equals(TEXT("uasset"), ESearchCase::IgnoreCase) || !IPlatformFile::GetPlatformPhysical().FileExists(*Filename))
		{
			OutReason = TEXT("it is stored inside a .pak or IoStore container, not as a file in the project");
			return false;
		}
		OutFilename = Filename;
		return true;
	}

	void ConvertDiscardTemporary(UMaterialInstanceConstant* Editable, UPackage* TempPackage)
	{
		if (Editable)
		{
			Editable->ClearFlags(RF_Public | RF_Standalone);
			Editable->MarkPendingKill();
		}
		if (TempPackage)
		{
			TempPackage->MarkPendingKill();
		}
	}

	void ConvertRunCommand(const TArray<FString>& Arguments)
	{
		if (Arguments.Num() == 0)
		{
			UE_LOG(LogRebirthCookedConversion, Display, TEXT("Usage: Rebirth.MakeEditable /Game/Path/Asset.Asset [/Game/Other/Asset.Asset ...]"));
			return;
		}
		TArray<UMaterialInstanceConstant*> Instances;
		for (const FString& Argument : Arguments)
		{
			FString ObjectPath = Argument;
			if (!ObjectPath.Contains(TEXT(".")))
			{
				ObjectPath += TEXT(".") + FPackageName::GetLongPackageAssetName(ObjectPath);
			}
			if (UMaterialInstanceConstant* Instance = LoadObject<UMaterialInstanceConstant>(nullptr, *ObjectPath))
			{
				Instances.Add(Instance);
			}
			else
			{
				UE_LOG(LogRebirthCookedConversion, Warning, TEXT("%s is not a loadable material instance."), *Argument);
			}
		}
		TArray<FString> Messages;
		FString BackupFolder;
		const int32 Converted = RebirthCookedMaterialConversion::MakeEditable(Instances, Messages, BackupFolder);
		for (const FString& Message : Messages)
		{
			UE_LOG(LogRebirthCookedConversion, Display, TEXT("%s"), *Message);
		}
		UE_LOG(LogRebirthCookedConversion, Display, TEXT("%d of %d material instance(s) made editable.%s"), Converted, Instances.Num(),
			Converted > 0 ? *FString::Printf(TEXT(" Cooked originals: %s"), *BackupFolder) : TEXT(""));
	}
}

namespace RebirthCookedMaterialConversion
{
	void Register()
	{
		if (IsRunningCommandlet() || GConvertCommand.IsValid())
		{
			return;
		}
		GConvertCommand = MakeUnique<FAutoConsoleCommand>(TEXT("Rebirth.MakeEditable"),
			TEXT("Make cooked material instances editable in place (the cooked files are kept in Saved/RebirthCookedOriginals): Rebirth.MakeEditable /Game/Path/Asset.Asset ..."),
			FConsoleCommandWithArgsDelegate::CreateStatic(&ConvertRunCommand));
	}

	void Unregister()
	{
		GConvertCommand.Reset();
	}

	TArray<TWeakObjectPtr<UMaterialInstanceConstant>> GetConvertible(const TArray<UObject*>& Objects)
	{
		TArray<TWeakObjectPtr<UMaterialInstanceConstant>> Result;
		for (UObject* Object : Objects)
		{
			UMaterialInstanceConstant* Instance = Cast<UMaterialInstanceConstant>(Object);
			if (Instance && ConvertIsCookedPackage(Instance))
			{
				Result.Add(Instance);
			}
		}
		return Result;
	}

	int32 MakeEditable(const TArray<UMaterialInstanceConstant*>& Instances, TArray<FString>& OutMessages, FString& OutBackupFolder)
	{
		if (!IsInGameThread() || GIsSavingPackage || IsGarbageCollecting())
		{
			OutMessages.Add(TEXT("The editor is busy saving or collecting garbage; try again."));
			return 0;
		}
		FlushAsyncLoading();

		IPlatformFile& Physical = IPlatformFile::GetPlatformPhysical();
		OutBackupFolder = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir() / TEXT("RebirthCookedOriginals") / FDateTime::Now().ToString(TEXT("%Y%m%d-%H%M%S")));
		UAssetEditorSubsystem* Editors = GEditor ? GEditor->GetEditorSubsystem<UAssetEditorSubsystem>() : nullptr;

		TArray<UPackage*> PackagesToReload;
		TArray<FString> SavedFiles;
		TArray<FString> Manifest;
		for (UMaterialInstanceConstant* Cooked : Instances)
		{
			FString Filename;
			FString Reason;
			if (!ConvertCheck(Cooked, Filename, Reason))
			{
				OutMessages.Add(FString::Printf(TEXT("%s: not converted, %s."), *GetPathNameSafe(Cooked), *Reason));
				continue;
			}
			UPackage* CookedPackage = Cooked->GetOutermost();
			const FString PackageName = CookedPackage->GetName();
			const FString ObjectPath = Cooked->GetPathName();

			UMaterialInterface* Parent = nullptr;
			FStaticParameterSet Static;
			FMaterialInstanceBasePropertyOverrides Overrides;
			ConvertOriginalState(Cooked, Parent, Static, Overrides);

			// 1. The editable copy: every property and subobject of the cooked instance, then its original parent chain
			//    state (the in-memory preview redirect only exists in this session).
			UPackage* TempPackage = CreatePackage(*FString::Printf(TEXT("/Temp/RebirthEditable/%s_%s"), *Cooked->GetName(), *FGuid::NewGuid().ToString(EGuidFormats::Digits)));
			UMaterialInstanceConstant* Editable = TempPackage ? DuplicateObject<UMaterialInstanceConstant>(Cooked, TempPackage, Cooked->GetFName()) : nullptr;
			if (!Editable)
			{
				ConvertDiscardTemporary(nullptr, TempPackage);
				OutMessages.Add(FString::Printf(TEXT("%s: not converted, the instance could not be copied."), *ObjectPath));
				continue;
			}
			Editable->ClearFlags(RF_Transient | RF_WasLoaded);
			Editable->SetFlags(RF_Public | RF_Standalone | RF_Transactional);
			Editable->Parent = Parent;
			const_cast<FStaticParameterSet&>(Editable->GetStaticParameters()) = Static;
			Editable->BasePropertyOverrides = Overrides;
			const bool bOwnPermutation = Parent != nullptr && (!Static.IsEmpty() || ConvertHasOverrideFlags(Overrides));
			Editable->bHasStaticPermutationResource = bOwnPermutation;

			// 2. Release the cooked files and move them to the backup folder.
			if (Editors)
			{
				Editors->CloseAllEditorsForAsset(Cooked);
			}
			CookedPackage->FullyLoad();
			ResetLoaders(CookedPackage);
			const FString BaseFilename = FPaths::GetBaseFilename(Filename, false);
			const FString RelativePath = PackageName.Mid(1); // "Game/Character/..."
			TArray<TPair<FString, FString>> Moved;
			bool bMoveFailed = false;
			static const TCHAR* const Extensions[] = { TEXT(".uasset"), TEXT(".uexp"), TEXT(".ubulk"), TEXT(".uptnl") };
			for (const TCHAR* Extension : Extensions)
			{
				const FString Source = BaseFilename + Extension;
				if (!Physical.FileExists(*Source))
				{
					continue;
				}
				const FString Target = OutBackupFolder / RelativePath + Extension;
				Physical.CreateDirectoryTree(*FPaths::GetPath(Target));
				if (!Physical.MoveFile(*Target, *Source))
				{
					bMoveFailed = true;
					break;
				}
				Moved.Emplace(Source, Target);
			}
			auto RestoreMoved = [&Physical, &Moved]()
			{
				for (const TPair<FString, FString>& Pair : Moved)
				{
					Physical.MoveFile(*Pair.Key, *Pair.Value);
				}
			};
			if (bMoveFailed)
			{
				RestoreMoved();
				ConvertDiscardTemporary(Editable, TempPackage);
				OutMessages.Add(FString::Printf(TEXT("%s: not converted, its cooked files could not be moved (open in another program?)."), *ObjectPath));
				continue;
			}

			// 3. Save the editable copy where the cooked package was.
			const bool bSaved = UPackage::SavePackage(TempPackage, Editable, RF_Public | RF_Standalone, *Filename, GError, nullptr, false, true, SAVE_NoError);
			if (!bSaved || !Physical.FileExists(*Filename))
			{
				Physical.DeleteFile(*Filename);
				RestoreMoved();
				ConvertDiscardTemporary(Editable, TempPackage);
				OutMessages.Add(FString::Printf(TEXT("%s: not converted, saving the editable copy failed (the cooked files were put back)."), *ObjectPath));
				continue;
			}
			ConvertDiscardTemporary(Editable, TempPackage);
			PackagesToReload.Add(CookedPackage);
			SavedFiles.Add(Filename);
			for (const TPair<FString, FString>& Pair : Moved)
			{
				Manifest.Add(FString::Printf(TEXT("%s\t%s"), *Pair.Value, *Pair.Key));
			}
			OutMessages.Add(FString::Printf(TEXT("%s: now editable (parent %s%s)."), *ObjectPath, *GetPathNameSafe(Parent),
				bOwnPermutation ? TEXT(", keeps its own static switches") : TEXT("")));
			UE_LOG(LogRebirthCookedConversion, Display, TEXT("Made %s editable; cooked files moved to %s"), *ObjectPath, *(OutBackupFolder / RelativePath));
		}

		if (PackagesToReload.Num() == 0)
		{
			return 0;
		}
		Manifest.Insert(TEXT("# Cooked originals moved by Rebirth Make Editable. To undo: close the editor, then move each file back (backup<TAB>original)."), 0);
		FFileHelper::SaveStringArrayToFile(Manifest, *(OutBackupFolder / TEXT("RestoreManifest.txt")));

		// 4. The asset registry learns about the new files (it does not watch direct package saves), then the cooked
		//    objects in memory are replaced by the editable ones; every reference is re-pointed by the reload.
		IAssetRegistry& Registry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();
		Registry.ScanFilesSynchronous(SavedFiles, true);
		FText ReloadError;
		if (!UPackageTools::ReloadPackages(PackagesToReload, ReloadError, EReloadPackagesInteractionMode::AssumePositive))
		{
			OutMessages.Add(FString::Printf(TEXT("The editable files are saved, but reloading them failed (%s). Restart the editor to use them."), *ReloadError.ToString()));
		}
		return SavedFiles.Num();
	}

	void MakeEditableWithDialog(const TArray<TWeakObjectPtr<UMaterialInstanceConstant>>& Instances)
	{
		TArray<UMaterialInstanceConstant*> Live;
		for (const TWeakObjectPtr<UMaterialInstanceConstant>& Weak : Instances)
		{
			if (UMaterialInstanceConstant* Instance = Weak.Get()) { Live.Add(Instance); }
		}
		if (Live.Num() == 0)
		{
			return;
		}
		const FText Question = FText::FromString(FString::Printf(
			TEXT("Make %d cooked material instance(s) editable?\n\n")
			TEXT("Each one becomes a normal Material Instance at the same path, with the same parent, parameters, static switches and overrides, so meshes and other materials keep using it. ")
			TEXT("The cooked files are moved to Saved/RebirthCookedOriginals/ (with a RestoreManifest.txt to put them back).\n\n")
			TEXT("Mods you package do not include /Game assets: to ship a change, duplicate the editable instance into your mod's folder."),
			Live.Num()));
		if (FMessageDialog::Open(EAppMsgType::OkCancel, Question) != EAppReturnType::Ok)
		{
			return;
		}
		TArray<FString> Messages;
		FString BackupFolder;
		const int32 Converted = MakeEditable(Live, Messages, BackupFolder);
		FString Report = FString::Printf(TEXT("%d of %d made editable."), Converted, Live.Num());
		if (Converted > 0)
		{
			Report += TEXT("\nCooked originals: ") + BackupFolder;
		}
		Report += TEXT("\n\n") + FString::Join(Messages, TEXT("\n"));
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Report));
	}
}
