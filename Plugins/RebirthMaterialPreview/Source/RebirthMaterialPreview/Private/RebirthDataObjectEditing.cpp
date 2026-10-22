#include "RebirthDataObjectEditing.h"

#include "RebirthDataObjectFormat.h"
#include "RebirthDataObjectGame.h"
#include "RebirthDataObjectSerialization.h"

#include "AssetRegistry/AssetData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "ContentBrowserModule.h"
#include "Editor.h"
#include "EditorStyleSet.h"
#include "EndDataObjectBase.h"
#include "Framework/Application/SlateApplication.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/IConsoleManager.h"
#include "HAL/PlatformFilemanager.h"
#include "IContentBrowserSingleton.h"
#include "Logging/LogMacros.h"
#include "Misc/DateTime.h"
#include "Misc/FileHelper.h"
#include "Misc/Guid.h"
#include "Misc/MessageDialog.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "Misc/ScopedSlowTask.h"
#include "Modules/ModuleManager.h"
#include "PackageTools.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "TimerManager.h"
#include "ToolMenus.h"
#include "UObject/Linker.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/UObjectHash.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SWindow.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Views/STableRow.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthDataObjectEditing, Log, All);

namespace RebirthDataObjectEditingDetail
{
	const FName DataObjectMenuOwner(TEXT("RebirthDataObjects"));
	FDelegateHandle GDataObjectMenuStartup;
	TUniquePtr<FAutoConsoleCommand> GImportDataObjectCommand;
	TUniquePtr<FAutoConsoleCommand> GMakeDataObjectEditableCommand;

	FString GCachedPaksDirectory;
	TArray<RebirthDataObjectGame::FGameFile> GCachedGameFiles;

	FString NewBackupFolder()
	{
		return FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir() / TEXT("RebirthDataObjectBackups") / FDateTime::Now().ToString(TEXT("%Y%m%d-%H%M%S")));
	}

	void WriteManifest(const FString& BackupFolder, TArray<FString> Lines)
	{
		if (Lines.Num() == 0)
		{
			return;
		}
		Lines.Insert(TEXT("# Files replaced by Rebirth data object tools. To undo: close the editor, then move each file back (backup<TAB>original)."), 0);
		FFileHelper::SaveStringArrayToFile(Lines, *(BackupFolder / TEXT("RestoreManifest.txt")));
	}

	UPackage* NewTemporaryPackage(const FString& Name)
	{
		return CreatePackage(*FString::Printf(TEXT("/Temp/RebirthDataObjects/%s_%s"), *Name, *FGuid::NewGuid().ToString(EGuidFormats::Digits)));
	}

	void DiscardTemporary(UObject* Object)
	{
		if (!Object)
		{
			return;
		}
		if (UEndDataObjectBase* DataObject = Cast<UEndDataObjectBase>(Object))
		{
			DataObject->EmptyTable();
		}
		UPackage* Package = Object->GetOutermost();
		Object->ClearFlags(RF_Public | RF_Standalone);
		Object->MarkPendingKill();
		if (Package)
		{
			Package->MarkPendingKill();
		}
	}

	/**
	 * Saves Editable (an object in a temporary package) as the asset at TargetPackageName. Files already at that path move
	 * to BackupFolder first; a package already loaded at that path is reloaded from the new file.
	 */
	bool SaveAsAsset(UEndDataObjectBase* Editable, const FString& TargetPackageName, const FString& BackupFolder, TArray<FString>& InOutManifest, FString& OutError)
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
		Package->ClearPackageFlags(PKG_MemoryMappedAsset | PKG_Cooked | PKG_FilterEditorOnly | PKG_UnversionedProperties);
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
				UE_LOG(LogRebirthDataObjectEditing, Warning, TEXT("%s is saved, but reloading it failed (%s); restart the editor to use it."), *TargetPackageName, *ReloadError.ToString());
			}
		}
		return true;
	}

	bool GetGameFiles(const FString& PaksDirectory, TArray<RebirthDataObjectGame::FGameFile>& OutFiles, FString& OutError)
	{
		if (GCachedPaksDirectory == PaksDirectory && GCachedGameFiles.Num() > 0)
		{
			OutFiles = GCachedGameFiles;
			return true;
		}
		if (!RebirthDataObjectGame::ListDataObjects(PaksDirectory, OutFiles, OutError))
		{
			return false;
		}
		GCachedPaksDirectory = PaksDirectory;
		GCachedGameFiles = OutFiles;
		return true;
	}

	bool NamesMatch(const RebirthDataObjectFormat::FImage& Image, const TMap<uint32, FName>& NamesAt)
	{
		int32 Count = 0;
		for (const TPair<FName, TArray<uint32>>& Entry : Image.Names)
		{
			for (const uint32 Offset : Entry.Value)
			{
				const FName* Found = NamesAt.Find(Offset);
				if (!Found || *Found != Entry.Key || !Found->GetPlainNameString().Equals(Entry.Key.GetPlainNameString(), ESearchCase::CaseSensitive))
				{
					return false;
				}
				++Count;
			}
		}
		return Count == NamesAt.Num();
	}

	void OpenEditorFor(const FString& PackageName)
	{
		if (!GEditor)
		{
			return;
		}
		if (UObject* Asset = RebirthDataObjectEditing::FindDataObject(PackageName))
		{
			if (UAssetEditorSubsystem* Editors = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
			{
				Editors->OpenEditorForAsset(Asset);
			}
			FContentBrowserModule& ContentBrowser = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
			ContentBrowser.Get().SyncBrowserToAssets(TArray<FAssetData>{ FAssetData(Asset) });
		}
	}

	FString PickGameDataObject(const TArray<FString>& PackageNames, const FString& InitialSelection)
	{
		struct FPickerState
		{
			TArray<TSharedPtr<FString>> All;
			TArray<TSharedPtr<FString>> Shown;
			TSharedPtr<SListView<TSharedPtr<FString>>> List;
			TSharedPtr<SWindow> Window;
			FString Chosen;

			void Filter(const FString& Text)
			{
				Shown.Reset();
				for (const TSharedPtr<FString>& Item : All)
				{
					if (Text.IsEmpty() || Item->Contains(Text))
					{
						Shown.Add(Item);
					}
				}
				if (List.IsValid())
				{
					List->RequestListRefresh();
				}
			}

			void Accept(const TSharedPtr<FString>& Item)
			{
				if (Item.IsValid())
				{
					Chosen = *Item;
					if (Window.IsValid())
					{
						Window->RequestDestroyWindow();
					}
				}
			}
		};
		TSharedRef<FPickerState> State = MakeShared<FPickerState>();
		TSharedPtr<FString> Initial;
		for (const FString& PackageName : PackageNames)
		{
			State->All.Add(MakeShared<FString>(PackageName));
			if (PackageName == InitialSelection)
			{
				Initial = State->All.Last();
			}
		}
		State->Shown = State->All;

		State->Window = SNew(SWindow)
			.Title(FText::FromString(TEXT("Import Data Object from Game")))
			.ClientSize(FVector2D(680.f, 560.f))
			.SupportsMinimize(false)
			.SupportsMaximize(false)
			[
				SNew(SBorder)
				.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
				.Padding(8.f)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 0.f, 0.f, 6.f)
					[
						SNew(STextBlock)
						.AutoWrapText(true)
						.Text(FText::FromString(TEXT("Pick one of the game's data objects. It becomes an editable asset at the same path in this project (an existing one is moved to Saved/RebirthDataObjectBackups/). Edit it in the Data Object table editor; Package Project ships it in the game's format.")))
					]
					+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 0.f, 0.f, 6.f)
					[
						SNew(SSearchBox)
						.OnTextChanged_Lambda([State](const FText& Text) { State->Filter(Text.ToString()); })
					]
					+ SVerticalBox::Slot().FillHeight(1.f)
					[
						SAssignNew(State->List, SListView<TSharedPtr<FString>>)
						.ListItemsSource(&State->Shown)
						.SelectionMode(ESelectionMode::Single)
						.OnGenerateRow_Lambda([](TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& Owner) -> TSharedRef<ITableRow>
						{
							return SNew(STableRow<TSharedPtr<FString>>, Owner)[SNew(STextBlock).Text(FText::FromString(*Item))];
						})
						.OnMouseButtonDoubleClick_Lambda([State](TSharedPtr<FString> Item) { State->Accept(Item); })
					]
					+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Right).Padding(0.f, 6.f, 0.f, 0.f)
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().AutoWidth().Padding(0.f, 0.f, 6.f, 0.f)
						[
							SNew(SButton)
							.Text(FText::FromString(TEXT("Import")))
							.OnClicked_Lambda([State]()
							{
								const TArray<TSharedPtr<FString>> Selected = State->List->GetSelectedItems();
								if (Selected.Num() > 0)
								{
									State->Accept(Selected[0]);
								}
								return FReply::Handled();
							})
						]
						+ SHorizontalBox::Slot().AutoWidth()
						[
							SNew(SButton)
							.Text(FText::FromString(TEXT("Cancel")))
							.OnClicked_Lambda([State]()
							{
								State->Window->RequestDestroyWindow();
								return FReply::Handled();
							})
						]
					]
				]
			];
		if (Initial.IsValid())
		{
			State->List->SetSelection(Initial);
			State->List->RequestScrollIntoView(Initial);
		}
		GEditor->EditorAddModalWindow(State->Window.ToSharedRef());
		const FString Chosen = State->Chosen;
		// The widgets hold the state through their lambdas; break the cycle.
		State->List.Reset();
		State->Window.Reset();
		return Chosen;
	}

	void RunImportCommand(const TArray<FString>& Arguments)
	{
		if (Arguments.Num() < 1)
		{
			UE_LOG(LogRebirthDataObjectEditing, Display, TEXT("Usage: Rebirth.ImportDataObject /Game/DataObject/Resident/CharaSpec [GamePaksFolder]"));
			return;
		}
		FString Message;
		const bool bImported = RebirthDataObjectEditing::ImportFromGame(Arguments[0], Arguments.Num() > 1 ? Arguments[1] : FString(), Message);
		UE_LOG(LogRebirthDataObjectEditing, Display, TEXT("%s%s"), bImported ? TEXT("") : TEXT("Not imported: "), *Message);
	}

	void RunMakeEditableCommand(const TArray<FString>& Arguments)
	{
		TArray<UEndDataObjectBase*> DataObjects;
		for (const FString& Argument : Arguments)
		{
			if (UEndDataObjectBase* DataObject = RebirthDataObjectEditing::FindDataObject(Argument))
			{
				DataObjects.Add(DataObject);
			}
			else
			{
				UE_LOG(LogRebirthDataObjectEditing, Warning, TEXT("%s is not a loadable data object."), *Argument);
			}
		}
		TArray<FString> Messages;
		FString BackupFolder;
		const int32 Converted = RebirthDataObjectEditing::MakeEditable(DataObjects, Messages, BackupFolder);
		for (const FString& Message : Messages)
		{
			UE_LOG(LogRebirthDataObjectEditing, Display, TEXT("%s"), *Message);
		}
		UE_LOG(LogRebirthDataObjectEditing, Display, TEXT("%d of %d data object(s) made editable."), Converted, DataObjects.Num());
	}

	void RegisterDataObjectMenus()
	{
		FToolMenuOwnerScoped OwnerScoped(DataObjectMenuOwner);
		const FText Label = FText::FromString(TEXT("Import Data Object from Game..."));
		const FText ToolTip = FText::FromString(TEXT("Create an editable copy of one of the game's data objects (CharaSpec, Equipment, ...) at its game path. Package Project ships it in the game's format."));
		static const FName Menus[] = { FName(TEXT("LevelEditor.MainMenu.File")), FName(TEXT("ContentBrowser.AddNewContextMenu")) };
		for (const FName MenuName : Menus)
		{
			if (UToolMenu* Menu = UToolMenus::Get()->ExtendMenu(MenuName))
			{
				FToolMenuSection& Section = Menu->FindOrAddSection(TEXT("RebirthDataObjects"));
				Section.Label = FText::FromString(TEXT("Rebirth"));
				Section.AddMenuEntry(TEXT("RebirthImportDataObject"), Label, ToolTip, FSlateIcon(),
					FUIAction(FExecuteAction::CreateStatic(&RebirthDataObjectEditing::OpenImportDialog)));
			}
		}
	}
}

namespace RebirthDataObjectEditing
{
	using namespace RebirthDataObjectEditingDetail;
	void Register()
	{
		if (IsRunningCommandlet() || GDataObjectMenuStartup.IsValid())
		{
			return;
		}
		GDataObjectMenuStartup = UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateStatic(&RegisterDataObjectMenus));
		GImportDataObjectCommand = MakeUnique<FAutoConsoleCommand>(TEXT("Rebirth.ImportDataObject"),
			TEXT("Import one of the game's data objects as an editable asset at its game path: Rebirth.ImportDataObject /Game/DataObject/Resident/CharaSpec [GamePaksFolder]"),
			FConsoleCommandWithArgsDelegate::CreateStatic(&RunImportCommand));
		GMakeDataObjectEditableCommand = MakeUnique<FAutoConsoleCommand>(TEXT("Rebirth.MakeDataObjectEditable"),
			TEXT("Make cooked data objects in the project editable in place (the cooked files go to Saved/RebirthDataObjectBackups): Rebirth.MakeDataObjectEditable /Game/DataObject/Resident/CharaSpec ..."),
			FConsoleCommandWithArgsDelegate::CreateStatic(&RunMakeEditableCommand));
	}

	void Unregister()
	{
		if (GDataObjectMenuStartup.IsValid())
		{
			UToolMenus::UnRegisterStartupCallback(GDataObjectMenuStartup);
			GDataObjectMenuStartup.Reset();
			// The tool menus are UObjects: only touch them while UObjects still exist.
			if (UObjectInitialized() && !IsEngineExitRequested())
			{
				UToolMenus::UnregisterOwner(DataObjectMenuOwner);
			}
		}
		GImportDataObjectCommand.Reset();
		GMakeDataObjectEditableCommand.Reset();
		GCachedGameFiles.Reset();
		GCachedPaksDirectory.Reset();
	}

	bool IsConvertible(const UObject* Object)
	{
		const UEndDataObjectBase* DataObject = Cast<UEndDataObjectBase>(Object);
		return DataObject && !DataObject->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject) && DataObject->GetOuter() == DataObject->GetOutermost()
			&& RebirthDataObjects::IsCookedDataObject(DataObject);
	}

	TArray<TWeakObjectPtr<UEndDataObjectBase>> GetConvertible(const TArray<UObject*>& Objects)
	{
		TArray<TWeakObjectPtr<UEndDataObjectBase>> Result;
		for (UObject* Object : Objects)
		{
			if (IsConvertible(Object))
			{
				Result.Add(CastChecked<UEndDataObjectBase>(Object));
			}
		}
		return Result;
	}

	UEndDataObjectBase* FindDataObject(const FString& PathOrPackage)
	{
		if (PathOrPackage.IsEmpty())
		{
			return nullptr;
		}
		if (PathOrPackage.Contains(TEXT(".")))
		{
			return LoadObject<UEndDataObjectBase>(nullptr, *PathOrPackage);
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
		if (UEndDataObjectBase* Named = FindObject<UEndDataObjectBase>(Package, *FPackageName::GetLongPackageAssetName(PathOrPackage)))
		{
			return Named;
		}
		UEndDataObjectBase* Found = nullptr;
		ForEachObjectWithOuter(Package, [&Found](UObject* Object)
		{
			if (!Found && !Object->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
			{
				Found = Cast<UEndDataObjectBase>(Object);
			}
		}, false);
		return Found;
	}

	int32 MakeEditable(const TArray<UEndDataObjectBase*>& DataObjects, TArray<FString>& OutMessages, FString& OutBackupFolder)
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
		for (UEndDataObjectBase* Cooked : DataObjects)
		{
			if (!IsValid(Cooked) || !IsConvertible(Cooked))
			{
				OutMessages.Add(FString::Printf(TEXT("%s: not converted, it is not a cooked data object."), *GetPathNameSafe(Cooked)));
				continue;
			}
			const FString ObjectPath = Cooked->GetPathName();
			if (!RebirthDataObjects::HasGameLayout(*Cooked))
			{
				OutMessages.Add(FString::Printf(TEXT("%s: not converted, its rows could not be read (see the Output Log)."), *ObjectPath));
				continue;
			}
			const FString PackageName = Cooked->GetOutermost()->GetName();
			FString Filename;
			if (!FPackageName::DoesPackageExist(PackageName, nullptr, &Filename) || !FPaths::GetExtension(Filename).Equals(TEXT("uasset"), ESearchCase::IgnoreCase))
			{
				OutMessages.Add(FString::Printf(TEXT("%s: not converted, it is not a file in this project."), *ObjectPath));
				continue;
			}
			const int32 NumRows = Cooked->RowMap.Num();
			UPackage* TempPackage = NewTemporaryPackage(Cooked->GetName());
			UEndDataObjectBase* Editable = TempPackage ? DuplicateObject<UEndDataObjectBase>(Cooked, TempPackage, Cooked->GetFName()) : nullptr;
			if (!Editable || Editable->RowMap.Num() != NumRows || !RebirthDataObjects::HasGameLayout(*Editable))
			{
				DiscardTemporary(Editable);
				OutMessages.Add(FString::Printf(TEXT("%s: not converted, the rows could not be copied."), *ObjectPath));
				continue;
			}
			Editable->ClearFlags(RF_Transient | RF_WasLoaded);
			Editable->SetFlags(RF_Public | RF_Standalone | RF_Transactional);
			FString Error;
			const bool bSaved = SaveAsAsset(Editable, PackageName, OutBackupFolder, Manifest, Error);
			DiscardTemporary(Editable);
			if (!bSaved)
			{
				OutMessages.Add(FString::Printf(TEXT("%s: not converted, %s."), *ObjectPath, *Error));
				continue;
			}
			++Converted;
			OutMessages.Add(FString::Printf(TEXT("%s: now editable (%d rows)."), *ObjectPath, NumRows));
			UE_LOG(LogRebirthDataObjectEditing, Display, TEXT("Made %s editable (%d rows); cooked files moved to %s"), *ObjectPath, NumRows, *OutBackupFolder);
		}
		WriteManifest(OutBackupFolder, Manifest);
		return Converted;
	}

	void MakeEditableWithDialog(const TArray<TWeakObjectPtr<UEndDataObjectBase>>& DataObjects, bool bConfirm)
	{
		TArray<UEndDataObjectBase*> Live;
		TArray<FString> PackageNames;
		for (const TWeakObjectPtr<UEndDataObjectBase>& Weak : DataObjects)
		{
			if (UEndDataObjectBase* DataObject = Weak.Get())
			{
				Live.Add(DataObject);
				PackageNames.Add(DataObject->GetOutermost()->GetName());
			}
		}
		if (Live.Num() == 0)
		{
			return;
		}
		if (bConfirm)
		{
			const FText Question = FText::FromString(FString::Printf(
				TEXT("Make %d cooked data object(s) editable?\n\n")
				TEXT("Each one becomes a normal asset at the same path with all of its rows. It opens in the Data Object table editor, where rows can be edited, added, duplicated, renamed and deleted. ")
				TEXT("Package Project writes it back in the game's format at the same path, so the packaged pak replaces the game's file.\n\n")
				TEXT("The cooked files are moved to Saved/RebirthDataObjectBackups/ (with a RestoreManifest.txt to put them back)."),
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
			OpenEditorFor(PackageNames[0]);
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

	bool ImportFromGame(const FString& GamePackageName, const FString& PaksDirectory, FString& OutMessage, const FString& TargetPackageName)
	{
		FString PackageName = GamePackageName;
		int32 Dot = INDEX_NONE;
		if (PackageName.FindChar(TEXT('.'), Dot))
		{
			PackageName.LeftInline(Dot, false);
		}
		const FString Paks = PaksDirectory.IsEmpty() ? RebirthDataObjectGame::FindPaksDirectory(!IsRunningCommandlet()) : PaksDirectory;
		if (Paks.IsEmpty())
		{
			OutMessage = TEXT("The game's Paks folder was not found.");
			return false;
		}

		FScopedSlowTask Task(3.f, FText::FromString(FString::Printf(TEXT("Importing %s from the game"), *PackageName)));
		Task.MakeDialog();
		Task.EnterProgressFrame(1.f, FText::FromString(TEXT("Reading the game's containers")));
		TArray<RebirthDataObjectGame::FGameFile> Files;
		FString Error;
		if (!GetGameFiles(Paks, Files, Error))
		{
			OutMessage = FString::Printf(TEXT("The game's data objects could not be listed: %s."), *Error);
			return false;
		}
		const RebirthDataObjectGame::FGameFile* File = Files.FindByPredicate([&PackageName](const RebirthDataObjectGame::FGameFile& Candidate)
		{
			return Candidate.PackageName.Equals(PackageName, ESearchCase::IgnoreCase);
		});
		if (!File)
		{
			OutMessage = FString::Printf(TEXT("%s is not one of the game's data objects."), *PackageName);
			return false;
		}
		PackageName = File->PackageName;
		const FString Target = TargetPackageName.IsEmpty() ? PackageName : TargetPackageName;

		Task.EnterProgressFrame(1.f, FText::FromString(TEXT("Reading the data object")));
		TArray<uint8> Bytes;
		RebirthDataObjectGame::FGameDataObject Game;
		if (!RebirthDataObjectGame::ReadPackage(*File, Bytes, Error) || !RebirthDataObjectGame::DecodePackage(Bytes, Game, Error))
		{
			OutMessage = FString::Printf(TEXT("%s could not be read: %s."), *PackageName, *Error);
			return false;
		}
		const UScriptStruct* RowStruct = Game.Class->GetDefaultObject<UEndDataObjectBase>()->RowStruct;

		// Rebuilding the game's data from the decoded rows must give the same bytes; this proves the rows are complete.
		bool bExact = false;
		{
			RebirthDataObjectFormat::FLayout Layout;
			FString CheckError;
			if (Layout.Build(RowStruct, Game.Decoded.FieldNames, Game.Decoded.FieldTypes, CheckError))
			{
				TArray<const uint8*> Rows;
				for (uint8* Row : Game.Decoded.Rows)
				{
					Rows.Add(Row);
				}
				RebirthDataObjectFormat::FImage Image;
				if (RebirthDataObjectFormat::Encode(Layout, Game.Decoded.RowNames, Rows, Image, CheckError))
				{
					bExact = Image.Content == Game.Content && NamesMatch(Image, Game.NamesAt);
				}
			}
		}

		Task.EnterProgressFrame(1.f, FText::FromString(TEXT("Saving the editable asset")));
		UPackage* TempPackage = NewTemporaryPackage(Game.ObjectName.ToString());
		UEndDataObjectBase* Created = NewObject<UEndDataObjectBase>(TempPackage, Game.Class, FName(*FPackageName::GetLongPackageAssetName(Target)), RF_Public | RF_Standalone | RF_Transactional);
		RebirthDataObjects::AssignDecoded(*Created, Game.Decoded);
		const int32 NumRows = Created->RowMap.Num();
		const FString BackupFolder = NewBackupFolder();
		TArray<FString> Manifest;
		const bool bSaved = SaveAsAsset(Created, Target, BackupFolder, Manifest, Error);
		DiscardTemporary(Created);
		if (!bSaved)
		{
			OutMessage = FString::Printf(TEXT("%s was read (%d rows) but %s."), *PackageName, NumRows, *Error);
			return false;
		}
		WriteManifest(BackupFolder, Manifest);
		OutMessage = FString::Printf(TEXT("%s imported from the game as %s: %d rows, %s."), *PackageName, *Target, NumRows,
			bExact ? TEXT("rebuilding it gives the game's file byte for byte") : TEXT("WARNING: rebuilding it does not give the game's exact bytes"));
		if (Manifest.Num() > 0)
		{
			OutMessage += FString::Printf(TEXT(" The previous files were moved to %s."), *BackupFolder);
		}
		UE_LOG(LogRebirthDataObjectEditing, Display, TEXT("%s"), *OutMessage);
		return true;
	}

	void OpenImportDialog()
	{
		const FString Paks = RebirthDataObjectGame::FindPaksDirectory(true);
		if (Paks.IsEmpty())
		{
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("The game's folder was not found. Pick the FINAL FANTASY VII REBIRTH folder (the one with ff7rebirth.exe) when asked.")));
			return;
		}
		TArray<RebirthDataObjectGame::FGameFile> Files;
		FString Error;
		{
			FScopedSlowTask Task(1.f, FText::FromString(TEXT("Reading the game's data objects")));
			Task.MakeDialog();
			Task.EnterProgressFrame(1.f);
			if (!GetGameFiles(Paks, Files, Error))
			{
				FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("The game's data objects could not be listed: %s."), *Error)));
				return;
			}
		}
		TArray<FString> PackageNames;
		for (const RebirthDataObjectGame::FGameFile& File : Files)
		{
			PackageNames.Add(File.PackageName);
		}
		const FString Chosen = PickGameDataObject(PackageNames, TEXT("/Game/DataObject/Resident/CharaSpec"));
		if (Chosen.IsEmpty())
		{
			return;
		}
		if (FPackageName::DoesPackageExist(Chosen))
		{
			const FText Question = FText::FromString(FString::Printf(
				TEXT("%s already exists in this project.\n\nReplace it with the game's version? The current files are moved to Saved/RebirthDataObjectBackups/ (with a RestoreManifest.txt), and unsaved changes to it are lost."),
				*Chosen));
			if (FMessageDialog::Open(EAppMsgType::OkCancel, Question) != EAppReturnType::Ok)
			{
				return;
			}
		}
		FString Message;
		if (ImportFromGame(Chosen, Paks, Message))
		{
			OpenEditorFor(Chosen);
		}
		else
		{
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Message));
		}
	}

	bool OfferMakeEditableOnOpen(UObject* Object)
	{
		if (IsRunningCommandlet() || !IsConvertible(Object) || !GEditor)
		{
			return false;
		}
		UEndDataObjectBase* DataObject = CastChecked<UEndDataObjectBase>(Object);
		const FText Question = FText::FromString(FString::Printf(
			TEXT("%s is a cooked copy of the game's data (%d rows).\n\n")
			TEXT("Make it editable? It becomes a normal asset at the same path that opens in the Data Object table editor, and Package Project ships it in the game's format. ")
			TEXT("The cooked files are moved to Saved/RebirthDataObjectBackups/.\n\n")
			TEXT("Yes: make it editable and open it.\nNo: open the read-only preview."),
			*DataObject->GetName(), DataObject->RowMap.Num()));
		const EAppReturnType::Type Answer = FMessageDialog::Open(EAppMsgType::YesNoCancel, Question);
		if (Answer == EAppReturnType::No)
		{
			return false;
		}
		if (Answer == EAppReturnType::Yes)
		{
			// Converting reloads the package; do it after the current open request has unwound.
			TWeakObjectPtr<UEndDataObjectBase> Weak(DataObject);
			GEditor->GetTimerManager()->SetTimerForNextTick(FTimerDelegate::CreateLambda([Weak]()
			{
				MakeEditableWithDialog({ Weak }, false);
			}));
		}
		return true;
	}
}
