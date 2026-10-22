#include "RebirthAssetLibrary.h"

#include "RebirthAssetConversion.h"
#include "RebirthBlueprintTools.h"
#include "RebirthCookedCopies.h"
#include "RebirthSafeLoad.h"
#include "RebirthGameReferences.h"
#include "RebirthPackageHeader.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/Blueprint.h"
#include "HAL/PlatformFilemanager.h"
#include "Interfaces/ITargetPlatform.h"
#include "Interfaces/ITargetPlatformManagerModule.h"
#include "Logging/LogMacros.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "UObject/LinkerLoad.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/UObjectHash.h"
#include "UObject/UnrealType.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthAssetLibrary, Log, All);

namespace RebirthAssetLibraryDetail
{
	/** Script callers only see the message when the call succeeds, so failures go to the log too. */
	bool Outcome(bool bSucceeded, const FString& Message)
	{
		if (bSucceeded)
		{
			UE_LOG(LogRebirthAssetLibrary, Display, TEXT("%s"), *Message);
		}
		else
		{
			UE_LOG(LogRebirthAssetLibrary, Warning, TEXT("%s"), *Message);
		}
		return bSucceeded;
	}

	/** The asset, or for a package of a game blueprint its class. */
	UObject* FindAssetOrClass(const FString& PathOrPackage)
	{
		if (UObject* Asset = RebirthAssetConversion::FindAsset(PathOrPackage))
		{
			return Asset;
		}
		if (!PathOrPackage.Contains(TEXT(".")))
		{
			const FString ClassPath = PathOrPackage + TEXT(".") + FPackageName::GetLongPackageAssetName(PathOrPackage) + TEXT("_C");
			return StaticLoadObject(UClass::StaticClass(), nullptr, *ClassPath, nullptr, LOAD_NoWarn | LOAD_Quiet);
		}
		return nullptr;
	}

	/** The object whose properties a script reads: the asset itself, or the class defaults of a blueprint. */
	UObject* PropertyTarget(UObject* Asset)
	{
		if (UBlueprint* Blueprint = Cast<UBlueprint>(Asset))
		{
			return Blueprint->GeneratedClass ? Blueprint->GeneratedClass->GetDefaultObject() : nullptr;
		}
		if (UClass* Class = Cast<UClass>(Asset))
		{
			return Class->GetDefaultObject();
		}
		return Asset;
	}

	/**
	 * SavePackage without a base object refuses packages that are not fully loaded. A package created in this session
	 * counts as fully loaded only until its file exists, unless something marked it; loaded packages finish loading.
	 */
	void EnsureFullyLoaded(UPackage* Package)
	{
		if (!Package || Package->IsFullyLoaded())
		{
			return;
		}
		if (FLinkerLoad::FindExistingLinkerForPackage(Package))
		{
			Package->FullyLoad();
		}
		else
		{
			Package->MarkAsFullyLoaded();
		}
	}

	bool SaveTo(UObject* Asset, FString& Message)
	{
		UPackage* Package = Asset->GetOutermost();
		EnsureFullyLoaded(Package);
		const FString Filename = FPaths::ConvertRelativePathToFull(FPackageName::LongPackageNameToFilename(Package->GetName(), FPackageName::GetAssetPackageExtension()));
		if (!UPackage::SavePackage(Package, Asset, RF_Public | RF_Standalone, *Filename, GError, nullptr, false, true, SAVE_NoError))
		{
			Message = FString::Printf(TEXT("Saving %s failed."), *Filename);
			return false;
		}
		Message = FString::Printf(TEXT("Saved %s."), *Filename);
		return true;
	}
}

bool URebirthAssetLibrary::MakeAssetEditable(const FString& PathOrPackage, FString& Message)
{
	UObject* Asset = RebirthAssetConversion::FindAsset(PathOrPackage);
	if (!Asset)
	{
		Message = FString::Printf(TEXT("%s is not a loadable asset."), *PathOrPackage);
		return RebirthAssetLibraryDetail::Outcome(false, Message);
	}
	TArray<FString> Messages;
	FString BackupFolder;
	const int32 Converted = RebirthAssetConversion::MakeEditable(TArray<UObject*>{ Asset }, Messages, BackupFolder);
	Message = FString::Join(Messages, TEXT("\n"));
	return RebirthAssetLibraryDetail::Outcome(Converted == 1, Message);
}

bool URebirthAssetLibrary::MakeEditableCopy(const FString& PathOrPackage, const FString& TargetPackageName, FString& Message)
{
	UObject* Asset = RebirthAssetConversion::FindAsset(PathOrPackage);
	if (!Asset)
	{
		Message = FString::Printf(TEXT("%s is not a loadable asset."), *PathOrPackage);
		return RebirthAssetLibraryDetail::Outcome(false, Message);
	}
	return RebirthAssetLibraryDetail::Outcome(RebirthAssetConversion::MakeEditableCopy(Asset, TargetPackageName, Message), Message);
}

TArray<FString> URebirthAssetLibrary::ListCookedDataAssets(const FString& Folder)
{
	FString Root = Folder;
	Root.RemoveFromEnd(TEXT("/"));
	TArray<FString> Result;
	for (const FName& Package : RebirthCookedCopies::FindPackages())
	{
		const FString Name = Package.ToString();
		if (!Root.IsEmpty() && !Name.StartsWith(Root + TEXT("/")))
		{
			continue;
		}
		FString Filename;
		RebirthPackageHeader::FHeader Header;
		FString Error;
		if (!FPackageName::DoesPackageExist(Name, nullptr, &Filename) || !RebirthPackageHeader::Read(Filename, Header, true, Error))
		{
			continue;
		}
		bool bBlueprint = false;
		for (int32 Index = 0; Index < Header.Exports.Num(); ++Index)
		{
			const FString ClassName = Header.GetExportClassName(Index).ToString();
			bBlueprint |= Header.Exports[Index].OuterIndex == 0 && ClassName.EndsWith(TEXT("BlueprintGeneratedClass"));
		}
		if (!bBlueprint)
		{
			Result.Add(Name);
		}
	}
	return Result;
}

TArray<FString> URebirthAssetLibrary::GetSafeLoadReport()
{
	TArray<FString> Result;
	if (!RebirthSafeLoad::IsActive())
	{
		Result.Add(FString::Printf(TEXT("(guard off: %s)"), *RebirthSafeLoad::GetInactiveReason()));
	}
	for (const FName& Package : RebirthSafeLoad::GetDamagedPackages())
	{
		FString Details;
		RebirthSafeLoad::WasPackageDamaged(Package, &Details);
		Result.Add(Package.ToString() + TEXT(": ") + Details);
	}
	return Result;
}

TArray<FString> URebirthAssetLibrary::GetAssetReferences(const FString& PathOrPackage)
{
	TArray<FString> Result;
	UObject* Asset = RebirthAssetLibraryDetail::FindAssetOrClass(PathOrPackage);
	if (!Asset)
	{
		return Result;
	}
	UPackage* Package = Asset->GetOutermost();
	TArray<UObject*> Objects;
	GetObjectsWithOuter(Package, Objects, true);
	TSet<UObject*> Referenced;
	for (UObject* Object : Objects)
	{
		TArray<UObject*> Found;
		FReferenceFinder Finder(Found, nullptr, false, true, false, false);
		Finder.FindReferences(Object);
		for (UObject* Reference : Found)
		{
			if (Reference && Reference->GetOutermost() != Package && !Reference->IsA<UPackage>()
				&& !FPackageName::IsScriptPackage(Reference->GetOutermost()->GetName()) && Reference->GetOutermost() != GetTransientPackage())
			{
				Referenced.Add(Reference);
			}
		}
	}
	for (UObject* Reference : Referenced)
	{
		Result.Add(Reference->GetPathName());
	}
	Result.Sort();
	return Result;
}

TArray<FString> URebirthAssetLibrary::GetGameReferencePackages()
{
	return RebirthGameReferences::GetStandInPackageNames();
}

int32 URebirthAssetLibrary::EnsureGameReferences(const FString& PackageName)
{
	return RebirthGameReferences::EnsureForPackage(PackageName);
}

FString URebirthAssetLibrary::DescribePackageHeader(const FString& PackageName)
{
	const FString Package = FPackageName::ObjectPathToPackageName(PackageName);
	FString Filename;
	if (!FPackageName::DoesPackageExist(Package, nullptr, &Filename))
	{
		return FString::Printf(TEXT("%s: no file in this project"), *Package);
	}
	RebirthPackageHeader::FHeader Header;
	FString Error;
	if (!RebirthPackageHeader::Read(Filename, Header, true, Error))
	{
		return FString::Printf(TEXT("%s: %s"), *Filename, *Error);
	}
	return FString::Printf(TEXT("%s: %s, %d imports, %d exports"), *Filename, Header.IsCooked() ? TEXT("cooked") : TEXT("editor format"),
		Header.Imports.Num(), Header.Exports.Num());
}

FString URebirthAssetLibrary::GetAssetProperty(const FString& PathOrPackage, const FString& PropertyName)
{
	UObject* Target = RebirthAssetLibraryDetail::PropertyTarget(RebirthAssetLibraryDetail::FindAssetOrClass(PathOrPackage));
	const FProperty* Property = Target ? FindFProperty<FProperty>(Target->GetClass(), *PropertyName) : nullptr;
	FString Text;
	if (Property)
	{
		Property->ExportTextItem(Text, Property->ContainerPtrToValuePtr<void>(Target), nullptr, Target, PPF_None);
	}
	return Text;
}

bool URebirthAssetLibrary::SetAssetProperty(const FString& PathOrPackage, const FString& PropertyName, const FString& Value, FString& Message)
{
	UObject* Target = RebirthAssetLibraryDetail::PropertyTarget(RebirthAssetLibraryDetail::FindAssetOrClass(PathOrPackage));
	const FProperty* Property = Target ? FindFProperty<FProperty>(Target->GetClass(), *PropertyName) : nullptr;
	if (!Property)
	{
		Message = FString::Printf(TEXT("%s has no property %s."), *PathOrPackage, *PropertyName);
		return RebirthAssetLibraryDetail::Outcome(false, Message);
	}
	Target->Modify();
	if (!Property->ImportText(*Value, Property->ContainerPtrToValuePtr<void>(Target), PPF_None, Target))
	{
		Message = FString::Printf(TEXT("\"%s\" is not a valid value for %s."), *Value, *PropertyName);
		return RebirthAssetLibraryDetail::Outcome(false, Message);
	}
	Target->MarkPackageDirty();
	Message = FString::Printf(TEXT("%s.%s set."), *PathOrPackage, *PropertyName);
	return RebirthAssetLibraryDetail::Outcome(true, Message);
}

bool URebirthAssetLibrary::DuplicateAsset(const FString& PathOrPackage, const FString& TargetPackageName, FString& Message)
{
	UObject* Source = RebirthAssetConversion::FindAsset(PathOrPackage);
	if (!Source || Source->GetOutermost()->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly) || Source->IsA<UBlueprint>() || Source->IsA<UClass>())
	{
		Message = FString::Printf(TEXT("%s is not an editable data asset (make it editable first; for blueprints create a child)."), *PathOrPackage);
		return RebirthAssetLibraryDetail::Outcome(false, Message);
	}
	if (FPackageName::DoesPackageExist(TargetPackageName) || FindPackage(nullptr, *TargetPackageName))
	{
		Message = FString::Printf(TEXT("%s already exists."), *TargetPackageName);
		return RebirthAssetLibraryDetail::Outcome(false, Message);
	}
	UPackage* Package = CreatePackage(*TargetPackageName);
	Package->MarkAsFullyLoaded();
	UObject* Copy = DuplicateObject<UObject>(Source, Package, FName(*FPackageName::GetLongPackageAssetName(TargetPackageName)));
	if (!Copy)
	{
		Message = TEXT("The asset could not be copied.");
		return RebirthAssetLibraryDetail::Outcome(false, Message);
	}
	Copy->ClearFlags(RF_Transient | RF_WasLoaded);
	Copy->SetFlags(RF_Public | RF_Standalone | RF_Transactional);
	FAssetRegistryModule::AssetCreated(Copy);
	Package->MarkPackageDirty();
	const bool bSaved = RebirthAssetLibraryDetail::SaveTo(Copy, Message);
	if (bSaved)
	{
		Message = FString::Printf(TEXT("%s duplicated as %s."), *Source->GetPathName(), *Copy->GetPathName());
	}
	return RebirthAssetLibraryDetail::Outcome(bSaved, Message);
}

bool URebirthAssetLibrary::SaveAsset(const FString& PathOrPackage, FString& Message)
{
	UObject* Asset = RebirthAssetConversion::FindAsset(PathOrPackage);
	if (!Asset || Asset->GetOutermost()->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly))
	{
		Message = FString::Printf(TEXT("%s is not an editable asset."), *PathOrPackage);
		return RebirthAssetLibraryDetail::Outcome(false, Message);
	}
	return RebirthAssetLibraryDetail::Outcome(RebirthAssetLibraryDetail::SaveTo(Asset, Message), Message);
}

bool URebirthAssetLibrary::CookAssetToFile(const FString& PathOrPackage, const FString& Filename, FString& Message)
{
	UObject* Asset = RebirthAssetLibraryDetail::FindAssetOrClass(PathOrPackage);
	if (!Asset)
	{
		Message = FString::Printf(TEXT("%s is not a loadable asset."), *PathOrPackage);
		return RebirthAssetLibraryDetail::Outcome(false, Message);
	}
	const ITargetPlatform* Platform = GetTargetPlatformManagerRef().FindTargetPlatform(TEXT("WindowsNoEditor"));
	if (!Platform)
	{
		Message = TEXT("The WindowsNoEditor target platform is not available.");
		return RebirthAssetLibraryDetail::Outcome(false, Message);
	}
	// As the cooker saves: every public object of the package (a blueprint's class is not standalone).
	UPackage* Package = Asset->GetOutermost();
	RebirthAssetLibraryDetail::EnsureFullyLoaded(Package);
	const uint32 PackageFlags = Package->GetPackageFlags();
	Package->SetPackageFlags(PKG_FilterEditorOnly);
	const FString FullFilename = FPaths::ConvertRelativePathToFull(Filename);
	IPlatformFile::GetPlatformPhysical().CreateDirectoryTree(*FPaths::GetPath(FullFilename));
	const bool bSaved = UPackage::SavePackage(Package, nullptr, RF_Public, *FullFilename, GError, nullptr, false, true,
		SAVE_NoError | SAVE_KeepGUID | SAVE_Unversioned, Platform);
	Package->SetPackageFlagsTo(PackageFlags);
	Message = bSaved ? FString::Printf(TEXT("Cooked %s to %s."), *Package->GetName(), *FullFilename)
		: FString::Printf(TEXT("Cooking %s to %s failed."), *Package->GetName(), *FullFilename);
	return RebirthAssetLibraryDetail::Outcome(bSaved, Message);
}

TArray<FString> URebirthAssetLibrary::ListGameBlueprints(const FString& Folder)
{
	TArray<RebirthBlueprintTools::FGameBlueprint> Blueprints;
	RebirthBlueprintTools::FindGameBlueprints(Folder, Blueprints);
	TArray<FString> Result;
	for (const RebirthBlueprintTools::FGameBlueprint& Blueprint : Blueprints)
	{
		Result.Add(Blueprint.ClassPath);
	}
	return Result;
}

bool URebirthAssetLibrary::CreateChildBlueprint(const FString& ParentClassOrPackage, const FString& TargetPackageName, FString& Message)
{
	FString Error;
	UClass* Parent = RebirthBlueprintTools::LoadGameBlueprintClass(ParentClassOrPackage, Error);
	if (!Parent)
	{
		// Any other loadable class (a native one, or an editable blueprint's class).
		UObject* Asset = RebirthAssetLibraryDetail::FindAssetOrClass(ParentClassOrPackage);
		UBlueprint* ParentBlueprint = Cast<UBlueprint>(Asset);
		Parent = ParentBlueprint ? ParentBlueprint->GeneratedClass.Get() : Cast<UClass>(Asset);
	}
	if (!Parent)
	{
		Message = FString::Printf(TEXT("%s is not a loadable class: %s"), *ParentClassOrPackage, *Error);
		return RebirthAssetLibraryDetail::Outcome(false, Message);
	}
	UBlueprint* Child = RebirthBlueprintTools::CreateChildBlueprint(Parent, TargetPackageName, Error);
	if (!Child)
	{
		Message = FString::Printf(TEXT("No child blueprint of %s: %s"), *Parent->GetPathName(), *Error);
		return RebirthAssetLibraryDetail::Outcome(false, Message);
	}
	Message = FString::Printf(TEXT("Created %s (parent %s, %s)."), *Child->GetPathName(), *Parent->GetPathName(),
		Child->Status == BS_Error ? TEXT("does NOT compile") : TEXT("compiles"));
	return RebirthAssetLibraryDetail::Outcome(Child->Status != BS_Error, Message);
}

FString URebirthAssetLibrary::GetBlueprintParent(const FString& PathOrPackage)
{
	UObject* Asset = RebirthAssetLibraryDetail::FindAssetOrClass(PathOrPackage);
	if (UBlueprint* Blueprint = Cast<UBlueprint>(Asset))
	{
		return GetPathNameSafe(Blueprint->ParentClass);
	}
	if (UClass* Class = Cast<UClass>(Asset))
	{
		return GetPathNameSafe(Class->GetSuperClass());
	}
	return FString();
}
