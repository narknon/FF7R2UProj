#include "RebirthAssetConversion.h"

#include "RebirthGameReferences.h"
#include "RebirthSafeLoad.h"

#include "Animation/AnimationAsset.h"
#include "Animation/Skeleton.h"
#include "AssetRegistry/AssetData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "ContentBrowserModule.h"
#include "Curves/CurveBase.h"
#include "Editor.h"
#include "Engine/Blueprint.h"
#include "Engine/CurveTable.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "Engine/Font.h"
#include "Engine/Level.h"
#include "Engine/StreamableRenderAsset.h"
#include "Engine/Texture.h"
#include "Engine/UserDefinedEnum.h"
#include "Engine/UserDefinedStruct.h"
#include "Engine/World.h"
#include "EndDataObjectBase.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/IConsoleManager.h"
#include "HAL/PlatformFilemanager.h"
#include "IContentBrowserSingleton.h"
#include "Logging/LogMacros.h"
#include "Materials/MaterialFunctionInterface.h"
#include "Materials/MaterialInterface.h"
#include "Misc/DateTime.h"
#include "Misc/FileHelper.h"
#include "Misc/Guid.h"
#include "Misc/MessageDialog.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"
#include "PackageTools.h"
#include "Particles/ParticleSystem.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "Sound/SoundBase.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "TimerManager.h"
#include "UObject/LinkerLoad.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/UObjectHash.h"
#include "UObject/UnrealType.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthAssetConversion, Log, All);

namespace RebirthAssetConversionDetail
{
	TUniquePtr<FAutoConsoleCommand> GMakeEditableCommand;

	bool IsCookedPackage(const UObject* Object)
	{
		const UPackage* Package = Object ? Object->GetOutermost() : nullptr;
		return Package && (Package->bIsCookedForEditor || Package->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly));
	}

	FString NewBackupFolder()
	{
		return FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir() / TEXT("RebirthDataAssetBackups") / FDateTime::Now().ToString(TEXT("%Y%m%d-%H%M%S")));
	}

	void WriteManifest(const FString& BackupFolder, TArray<FString> Lines)
	{
		if (Lines.Num() == 0)
		{
			return;
		}
		Lines.Insert(TEXT("# Files replaced by Rebirth Make Editable. To undo: close the editor, then move each file back (backup<TAB>original)."), 0);
		FFileHelper::SaveStringArrayToFile(Lines, *(BackupFolder / TEXT("RestoreManifest.txt")));
	}

	void DiscardTemporary(UObject* Object)
	{
		if (!Object)
		{
			return;
		}
		UPackage* Package = Object->GetOutermost();
		Object->ClearFlags(RF_Public | RF_Standalone);
		Object->MarkPendingKill();
		if (Package)
		{
			Package->MarkPendingKill();
		}
	}

	/** References that failed when the asset loaded and would now find a stand-in. */
	bool HasLostReferences(UPackage* Package)
	{
		FLinkerLoad* Linker = FLinkerLoad::FindExistingLinkerForPackage(Package);
		if (!Linker)
		{
			return true;
		}
		for (int32 Index = 0; Index < Linker->ImportMap.Num(); ++Index)
		{
			const FObjectImport& Import = Linker->ImportMap[Index];
			if (Import.XObject || Import.OuterIndex.IsNull())
			{
				continue;
			}
			FPackageIndex Top = FPackageIndex::FromImport(Index);
			for (int32 Guard = 0; Top.IsImport() && !Linker->Imp(Top).OuterIndex.IsNull() && Guard < 64; ++Guard)
			{
				Top = Linker->Imp(Top).OuterIndex;
			}
			if (Top.IsImport())
			{
				if (UPackage* TopPackage = FindObjectFast<UPackage>(nullptr, Linker->Imp(Top).ObjectName))
				{
					if (RebirthGameReferences::IsStandInPackage(TopPackage))
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	void OpenEditorFor(UObject* Asset)
	{
		if (!GEditor || !Asset)
		{
			return;
		}
		if (UAssetEditorSubsystem* Editors = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
		{
			Editors->OpenEditorForAsset(Asset);
		}
		FContentBrowserModule& ContentBrowser = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
		ContentBrowser.Get().SyncBrowserToAssets(TArray<FAssetData>{ FAssetData(Asset) });
	}

	void RunMakeEditableCommand(const TArray<FString>& Arguments)
	{
		TArray<UObject*> Assets;
		for (const FString& Argument : Arguments)
		{
			if (UObject* Asset = RebirthAssetConversion::FindAsset(Argument))
			{
				Assets.Add(Asset);
			}
			else
			{
				UE_LOG(LogRebirthAssetConversion, Warning, TEXT("%s is not a loadable asset."), *Argument);
			}
		}
		TArray<FString> Messages;
		FString BackupFolder;
		const int32 Converted = RebirthAssetConversion::MakeEditable(Assets, Messages, BackupFolder);
		for (const FString& Message : Messages)
		{
			UE_LOG(LogRebirthAssetConversion, Display, TEXT("%s"), *Message);
		}
		UE_LOG(LogRebirthAssetConversion, Display, TEXT("%d of %d asset(s) made editable."), Converted, Assets.Num());
	}
}

namespace RebirthAssetConversion
{
	using namespace RebirthAssetConversionDetail;

	void Register()
	{
		if (IsRunningCommandlet() || GMakeEditableCommand.IsValid())
		{
			return;
		}
		GMakeEditableCommand = MakeUnique<FAutoConsoleCommand>(TEXT("Rebirth.MakeDataAssetEditable"),
			TEXT("Make cooked data assets in the project editable in place (the cooked files go to Saved/RebirthDataAssetBackups): Rebirth.MakeDataAssetEditable /Game/DataAsset/Game/CharaSpec/CharaSpec_PC0000_00_Cloud_Standard ..."),
			FConsoleCommandWithArgsDelegate::CreateStatic(&RunMakeEditableCommand));
	}

	void Unregister()
	{
		GMakeEditableCommand.Reset();
	}

	bool IsPlainDataClass(const UClass* Class)
	{
		if (!Class || Class->IsChildOf(UClass::StaticClass()) || Class->IsChildOf(UEndDataObjectBase::StaticClass()))
		{
			return false;
		}
		// Cooked render, animation, audio and graph assets lose data in the cook that an editable asset would need.
		static const UClass* const Excluded[] = {
			UTexture::StaticClass(), UStreamableRenderAsset::StaticClass(), UMaterialInterface::StaticClass(), UMaterialFunctionInterface::StaticClass(),
			UAnimationAsset::StaticClass(), USkeleton::StaticClass(), UPhysicsAsset::StaticClass(), USoundBase::StaticClass(), UWorld::StaticClass(),
			ULevel::StaticClass(), UParticleSystem::StaticClass(), UFont::StaticClass(), UBlueprint::StaticClass(), UUserDefinedStruct::StaticClass(),
			UUserDefinedEnum::StaticClass(),
		};
		for (const UClass* Base : Excluded)
		{
			if (Class->IsChildOf(Base))
			{
				return false;
			}
		}
		for (const UClass* Current = Class; Current; Current = Current->GetSuperClass())
		{
			const FString Path = Current->GetPathName();
			if (Path == TEXT("/Script/AIModule.BehaviorTree") || Path == TEXT("/Script/AIModule.EnvQuery") || Path.StartsWith(TEXT("/Script/Niagara")))
			{
				return false;
			}
		}
		if (Class->IsChildOf(UDataAsset::StaticClass()) || Class->IsChildOf(UDataTable::StaticClass()) || Class->IsChildOf(UCurveTable::StaticClass())
			|| Class->IsChildOf(UCurveBase::StaticClass()))
		{
			return true;
		}
		// The game's own types (anim sets, asset packs, ...): native classes of the game modules.
		for (const UClass* Current = Class; Current; Current = Current->GetSuperClass())
		{
			if (!Current->HasAnyClassFlags(CLASS_Native))
			{
				continue;
			}
			const FString Package = Current->GetOutermost()->GetName();
			return Package.StartsWith(TEXT("/Script/End")) || Package.StartsWith(TEXT("/Script/SQEX")) || Package.StartsWith(TEXT("/Script/KBD"));
		}
		return false;
	}

	bool IsConvertible(const UObject* Object)
	{
		return Object && !Object->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject) && Object->GetOuter() == Object->GetOutermost()
			&& IsCookedPackage(Object) && !RebirthGameReferences::IsStandIn(Object) && IsPlainDataClass(Object->GetClass());
	}

	TArray<TWeakObjectPtr<UObject>> GetConvertible(const TArray<UObject*>& Objects)
	{
		TArray<TWeakObjectPtr<UObject>> Result;
		for (UObject* Object : Objects)
		{
			if (IsConvertible(Object))
			{
				Result.Add(Object);
			}
		}
		return Result;
	}

	UObject* FindAsset(const FString& PathOrPackage)
	{
		if (PathOrPackage.IsEmpty())
		{
			return nullptr;
		}
		if (PathOrPackage.Contains(TEXT(".")))
		{
			return StaticLoadObject(UObject::StaticClass(), nullptr, *PathOrPackage);
		}
		UPackage* Package = FindPackage(nullptr, *PathOrPackage);
		if (!Package || !Package->IsFullyLoaded())
		{
			if (!FPackageName::DoesPackageExist(PathOrPackage))
			{
				return nullptr;
			}
			Package = LoadPackage(nullptr, *PathOrPackage, LOAD_None);
		}
		if (!Package)
		{
			return nullptr;
		}
		if (UObject* Named = StaticFindObjectFast(UObject::StaticClass(), Package, FName(*FPackageName::GetLongPackageAssetName(PathOrPackage))))
		{
			return Named;
		}
		UObject* Found = nullptr;
		ForEachObjectWithOuter(Package, [&Found](UObject* Object)
		{
			if (!Found && Object->IsAsset())
			{
				Found = Object;
			}
		}, false);
		return Found;
	}

	bool SaveAsAsset(UObject* Editable, const FString& TargetPackageName, const FString& BackupFolder, TArray<FString>& InOutManifest, FString& OutError)
	{
		IPlatformFile& Physical = IPlatformFile::GetPlatformPhysical();
		FString Filename;
		if (!FPackageName::TryConvertLongPackageNameToFilename(TargetPackageName, Filename, FPackageName::GetAssetPackageExtension()))
		{
			OutError = FString::Printf(TEXT("%s is not a valid content path"), *TargetPackageName);
			return false;
		}
		Filename = FPaths::ConvertRelativePathToFull(Filename);

		UPackage* Existing = FindPackage(nullptr, *TargetPackageName);
		if (Existing)
		{
			if (UAssetEditorSubsystem* Editors = GEditor ? GEditor->GetEditorSubsystem<UAssetEditorSubsystem>() : nullptr)
			{
				TArray<UObject*> Objects;
				GetObjectsWithOuter(Existing, Objects, false);
				for (UObject* Object : Objects)
				{
					Editors->CloseAllEditorsForAsset(Object);
				}
			}
			Existing->FullyLoad();
			ResetLoaders(Existing);
		}

		const FString BaseFilename = FPaths::GetBaseFilename(Filename, false);
		const FString RelativePath = TargetPackageName.Mid(1);
		TArray<TPair<FString, FString>> Moved;
		auto RestoreMoved = [&Physical, &Moved]()
		{
			for (const TPair<FString, FString>& Pair : Moved)
			{
				Physical.MoveFile(*Pair.Key, *Pair.Value);
			}
			Moved.Reset();
		};
		static const TCHAR* const Extensions[] = { TEXT(".uasset"), TEXT(".uexp"), TEXT(".ubulk"), TEXT(".uptnl") };
		for (const TCHAR* Extension : Extensions)
		{
			const FString Source = BaseFilename + Extension;
			if (!Physical.FileExists(*Source))
			{
				continue;
			}
			const FString Target = BackupFolder / RelativePath + Extension;
			Physical.CreateDirectoryTree(*FPaths::GetPath(Target));
			if (!Physical.MoveFile(*Target, *Source))
			{
				RestoreMoved();
				OutError = FString::Printf(TEXT("%s could not be moved to the backup folder (is it open in another program?)"), *Source);
				return false;
			}
			Moved.Emplace(Source, Target);
		}

		Physical.CreateDirectoryTree(*FPaths::GetPath(Filename));
		UPackage* Package = Editable->GetOutermost();
		Package->ClearPackageFlags(PKG_Cooked | PKG_FilterEditorOnly | PKG_UnversionedProperties | PKG_MemoryMappedAsset);
		const bool bSaved = UPackage::SavePackage(Package, Editable, RF_Public | RF_Standalone, *Filename, GError, nullptr, false, true, SAVE_NoError);
		if (!bSaved || !Physical.FileExists(*Filename))
		{
			Physical.DeleteFile(*Filename);
			RestoreMoved();
			OutError = TEXT("saving the editable asset failed (the previous files were put back)");
			return false;
		}
		for (const TPair<FString, FString>& Pair : Moved)
		{
			InOutManifest.Add(FString::Printf(TEXT("%s\t%s"), *Pair.Value, *Pair.Key));
		}

		IAssetRegistry& Registry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();
		Registry.ScanFilesSynchronous(TArray<FString>{ Filename }, true);
		if (Existing)
		{
			FText ReloadError;
			if (!UPackageTools::ReloadPackages(TArray<UPackage*>{ Existing }, ReloadError, EReloadPackagesInteractionMode::AssumePositive))
			{
				UE_LOG(LogRebirthAssetConversion, Warning, TEXT("%s is saved, but reloading it failed (%s); restart the editor to use it."), *TargetPackageName, *ReloadError.ToString());
			}
		}
		return true;
	}

	int32 MakeEditable(const TArray<UObject*>& Assets, TArray<FString>& OutMessages, FString& OutBackupFolder)
	{
		if (!IsInGameThread() || GIsSavingPackage || IsGarbageCollecting())
		{
			OutMessages.Add(TEXT("The editor is busy saving or collecting garbage; try again."));
			return 0;
		}
		FlushAsyncLoading();
		OutBackupFolder = NewBackupFolder();
		TArray<FString> Manifest;
		int32 Converted = 0;
		for (UObject* Cooked : Assets)
		{
			if (!IsValid(Cooked) || !IsConvertible(Cooked))
			{
				OutMessages.Add(FString::Printf(TEXT("%s: not converted, it is not a cooked data asset."), *GetPathNameSafe(Cooked)));
				continue;
			}
			UPackage* CookedPackage = Cooked->GetOutermost();
			const FString PackageName = CookedPackage->GetName();
			const FString ObjectPath = Cooked->GetPathName();
			const FName AssetName = Cooked->GetFName();
			FString Filename;
			if (!FPackageName::DoesPackageExist(PackageName, nullptr, &Filename) || !FPaths::GetExtension(Filename).Equals(TEXT("uasset"), ESearchCase::IgnoreCase))
			{
				OutMessages.Add(FString::Printf(TEXT("%s: not converted, it is not a file in this project."), *ObjectPath));
				continue;
			}

			// 1. Keep its references to game assets that are not in the project; reload it when it lost some on load.
			TArray<FString> Missing;
			RebirthGameReferences::EnsureForPackage(PackageName, &Missing);
			if (Missing.Num() > 0 && HasLostReferences(CookedPackage))
			{
				FText ReloadError;
				if (!UPackageTools::ReloadPackages(TArray<UPackage*>{ CookedPackage }, ReloadError, EReloadPackagesInteractionMode::AssumePositive))
				{
					OutMessages.Add(FString::Printf(TEXT("%s: not converted, it could not be reloaded with its game references (%s)."), *ObjectPath, *ReloadError.ToString()));
					continue;
				}
				CookedPackage = FindPackage(nullptr, *PackageName);
				Cooked = CookedPackage ? StaticFindObjectFast(UObject::StaticClass(), CookedPackage, AssetName) : nullptr;
				if (!Cooked)
				{
					OutMessages.Add(FString::Printf(TEXT("%s: not converted, it could not be reloaded."), *ObjectPath));
					continue;
				}
			}

			// A package the cooked-load guard had to skip parts of would be saved with default values in their place.
			FString Damage;
			if (RebirthSafeLoad::WasPackageDamaged(CookedPackage->GetFName(), &Damage))
			{
				OutMessages.Add(FString::Printf(TEXT("%s: not converted. Part of it could not be read (%s), so an editable copy would lose the game's values. ")
					TEXT("The End project's class needs the game's properties first."), *ObjectPath, *Damage));
				continue;
			}

			// 2. The editable copy: every property and subobject.
			UPackage* TempPackage = CreatePackage(*FString::Printf(TEXT("/Temp/RebirthEditable/%s_%s"), *AssetName.ToString(), *FGuid::NewGuid().ToString(EGuidFormats::Digits)));
			UObject* Editable = TempPackage ? DuplicateObject<UObject>(Cooked, TempPackage, AssetName) : nullptr;
			if (!Editable)
			{
				OutMessages.Add(FString::Printf(TEXT("%s: not converted, it could not be copied."), *ObjectPath));
				continue;
			}
			Editable->ClearFlags(RF_Transient | RF_WasLoaded);
			Editable->SetFlags(RF_Public | RF_Standalone | RF_Transactional);

			// 3. Saved where the cooked package was; the cooked files go to the backup folder.
			FString Error;
			const bool bSaved = SaveAsAsset(Editable, PackageName, OutBackupFolder, Manifest, Error);
			DiscardTemporary(Editable);
			if (!bSaved)
			{
				OutMessages.Add(FString::Printf(TEXT("%s: not converted, %s."), *ObjectPath, *Error));
				continue;
			}
			++Converted;
			OutMessages.Add(Missing.Num() > 0
				? FString::Printf(TEXT("%s: now editable; its references to %d game package(s) that are not in this project are kept."), *ObjectPath, Missing.Num())
				: FString::Printf(TEXT("%s: now editable."), *ObjectPath));
			UE_LOG(LogRebirthAssetConversion, Display, TEXT("Made %s editable; cooked files moved to %s"), *ObjectPath, *OutBackupFolder);
		}
		WriteManifest(OutBackupFolder, Manifest);
		return Converted;
	}

	int32 RenameCharaSpecEntries(UObject* Asset, const FString& OldModel, const FString& NewModel)
	{
		int32 Renamed = 0;
		if (!Asset || OldModel.IsEmpty() || NewModel.IsEmpty() || OldModel.Equals(NewModel, ESearchCase::IgnoreCase))
		{
			return Renamed;
		}
		static const TCHAR* const Lists[] = { TEXT("AssetClassList"), TEXT("AssetDataList"), TEXT("AssetDataSoftList") };
		static const TCHAR* const Suffixes[] = { TEXT("_Class"), TEXT("_Data") };
		for (const TCHAR* ListName : Lists)
		{
			FArrayProperty* List = FindFProperty<FArrayProperty>(Asset->GetClass(), ListName);
			FStructProperty* Inner = List ? CastField<FStructProperty>(List->Inner) : nullptr;
			FNameProperty* NameProperty = Inner ? FindFProperty<FNameProperty>(Inner->Struct, TEXT("AssetName")) : nullptr;
			if (!NameProperty)
			{
				continue;
			}
			FScriptArrayHelper Helper(List, List->ContainerPtrToValuePtr<void>(Asset));
			for (int32 Index = 0; Index < Helper.Num(); ++Index)
			{
				uint8* Entry = Helper.GetRawPtr(Index);
				const FString Current = NameProperty->GetPropertyValue_InContainer(Entry).ToString();
				for (const TCHAR* Suffix : Suffixes)
				{
					if (Current.Equals(OldModel + Suffix, ESearchCase::IgnoreCase))
					{
						NameProperty->SetPropertyValue_InContainer(Entry, FName(*(NewModel + Suffix)));
						++Renamed;
					}
				}
			}
		}
		return Renamed;
	}

	bool MakeEditableCopy(UObject* Cooked, const FString& TargetPackageName, FString& OutMessage)
	{
		if (!IsInGameThread() || GIsSavingPackage || IsGarbageCollecting())
		{
			OutMessage = TEXT("The editor is busy saving or collecting garbage; try again.");
			return false;
		}
		if (!IsValid(Cooked) || !IsConvertible(Cooked))
		{
			OutMessage = FString::Printf(TEXT("%s is not a cooked data asset."), *GetPathNameSafe(Cooked));
			return false;
		}
		if (!FPackageName::IsValidLongPackageName(TargetPackageName) || FPackageName::DoesPackageExist(TargetPackageName) || FindPackage(nullptr, *TargetPackageName))
		{
			OutMessage = FString::Printf(TEXT("%s is not a free content path."), *TargetPackageName);
			return false;
		}
		FlushAsyncLoading();
		UPackage* CookedPackage = Cooked->GetOutermost();
		const FString PackageName = CookedPackage->GetName();
		const FString ObjectPath = Cooked->GetPathName();
		const FName AssetName = Cooked->GetFName();

		TArray<FString> Missing;
		RebirthGameReferences::EnsureForPackage(PackageName, &Missing);
		if (Missing.Num() > 0 && HasLostReferences(CookedPackage))
		{
			FText ReloadError;
			if (!UPackageTools::ReloadPackages(TArray<UPackage*>{ CookedPackage }, ReloadError, EReloadPackagesInteractionMode::AssumePositive))
			{
				OutMessage = FString::Printf(TEXT("%s could not be reloaded with its game references (%s)."), *ObjectPath, *ReloadError.ToString());
				return false;
			}
			CookedPackage = FindPackage(nullptr, *PackageName);
			Cooked = CookedPackage ? StaticFindObjectFast(UObject::StaticClass(), CookedPackage, AssetName) : nullptr;
			if (!Cooked)
			{
				OutMessage = FString::Printf(TEXT("%s could not be reloaded."), *ObjectPath);
				return false;
			}
		}
		FString Damage;
		if (RebirthSafeLoad::WasPackageDamaged(CookedPackage->GetFName(), &Damage))
		{
			OutMessage = FString::Printf(TEXT("%s: part of it could not be read (%s), so a copy would lose the game's values."), *ObjectPath, *Damage);
			return false;
		}

		const FString NewAssetName = FPackageName::GetLongPackageAssetName(TargetPackageName);
		UPackage* TempPackage = CreatePackage(*FString::Printf(TEXT("/Temp/RebirthEditable/%s_%s"), *NewAssetName, *FGuid::NewGuid().ToString(EGuidFormats::Digits)));
		UObject* Editable = TempPackage ? DuplicateObject<UObject>(Cooked, TempPackage, FName(*NewAssetName)) : nullptr;
		if (!Editable)
		{
			OutMessage = FString::Printf(TEXT("%s could not be copied."), *ObjectPath);
			return false;
		}
		Editable->ClearFlags(RF_Transient | RF_WasLoaded);
		Editable->SetFlags(RF_Public | RF_Standalone | RF_Transactional);

		int32 Renamed = 0;
		const FString Prefix = TEXT("CharaSpec_");
		const FString OldName = AssetName.ToString();
		if (OldName.StartsWith(Prefix) && NewAssetName.StartsWith(Prefix))
		{
			Renamed = RenameCharaSpecEntries(Editable, OldName.Mid(Prefix.Len()), NewAssetName.Mid(Prefix.Len()));
		}

		TArray<FString> Manifest;
		FString Error;
		const bool bSaved = SaveAsAsset(Editable, TargetPackageName, NewBackupFolder(), Manifest, Error);
		DiscardTemporary(Editable);
		if (!bSaved)
		{
			OutMessage = FString::Printf(TEXT("%s: the copy could not be saved, %s."), *ObjectPath, *Error);
			return false;
		}
		OutMessage = FString::Printf(TEXT("%s: editable copy saved as %s%s%s."), *ObjectPath, *TargetPackageName,
			Renamed > 0 ? *FString::Printf(TEXT(" (%d CharaSpec entr%s renamed after %s)"), Renamed, Renamed == 1 ? TEXT("y") : TEXT("ies"), *NewAssetName.Mid(Prefix.Len())) : TEXT(""),
			Missing.Num() > 0 ? *FString::Printf(TEXT("; its references to %d game package(s) that are not in this project are kept"), Missing.Num()) : TEXT(""));
		UE_LOG(LogRebirthAssetConversion, Display, TEXT("%s"), *OutMessage);
		return true;
	}

	void MakeEditableWithDialog(const TArray<TWeakObjectPtr<UObject>>& Assets, bool bConfirm)
	{
		TArray<UObject*> Live;
		TArray<FString> PackageNames;
		for (const TWeakObjectPtr<UObject>& Weak : Assets)
		{
			if (UObject* Asset = Weak.Get())
			{
				Live.Add(Asset);
				PackageNames.Add(Asset->GetOutermost()->GetName());
			}
		}
		if (Live.Num() == 0)
		{
			return;
		}
		if (bConfirm)
		{
			const FText Question = FText::FromString(FString::Printf(
				TEXT("Make %d cooked data asset(s) editable?\n\n")
				TEXT("Each one becomes a normal asset at the same path with all of its properties. References to game assets that are not in this project are kept. ")
				TEXT("Package Project ships it at its game path, so the packaged pak replaces the game's file. Duplicate it to make new ones (for example a new character's CharaSpec).\n\n")
				TEXT("The cooked files are moved to Saved/RebirthDataAssetBackups/ (with a RestoreManifest.txt to put them back)."),
				Live.Num()));
			if (FMessageDialog::Open(EAppMsgType::OkCancel, Question) != EAppReturnType::Ok)
			{
				return;
			}
		}
		TArray<FString> Messages;
		FString BackupFolder;
		const int32 Converted = MakeEditable(Live, Messages, BackupFolder);
		if (Converted == 1 && Live.Num() == 1)
		{
			OpenEditorFor(FindAsset(PackageNames[0]));
			return;
		}
		FString Report = FString::Printf(TEXT("%d of %d made editable."), Converted, Live.Num());
		if (Converted > 0)
		{
			Report += TEXT("\nCooked originals: ") + BackupFolder;
		}
		Report += TEXT("\n\n") + FString::Join(Messages, TEXT("\n"));
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Report));
	}

	bool OfferMakeEditableOnOpen(UObject* Object)
	{
		if (IsRunningCommandlet() || !IsConvertible(Object) || !GEditor)
		{
			return false;
		}
		const FText Question = FText::FromString(FString::Printf(
			TEXT("%s is a cooked copy of the game's data (%s).\n\n")
			TEXT("Make it editable? It becomes a normal asset at the same path, its references to game assets that are not in this project are kept, ")
			TEXT("and Package Project ships it. The cooked files are moved to Saved/RebirthDataAssetBackups/.\n\n")
			TEXT("Yes: make it editable and open it.\nNo: open the read-only preview."),
			*Object->GetName(), *Object->GetClass()->GetName()));
		const EAppReturnType::Type Answer = FMessageDialog::Open(EAppMsgType::YesNoCancel, Question);
		if (Answer == EAppReturnType::No)
		{
			return false;
		}
		if (Answer == EAppReturnType::Yes)
		{
			// Converting reloads the package; do it after the current open request has unwound.
			TWeakObjectPtr<UObject> Weak(Object);
			GEditor->GetTimerManager()->SetTimerForNextTick(FTimerDelegate::CreateLambda([Weak]()
			{
				MakeEditableWithDialog({ Weak }, false);
			}));
		}
		return true;
	}
}
