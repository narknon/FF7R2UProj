#include "RebirthBlueprintTools.h"

#include "RebirthGameReferences.h"
#include "RebirthPackageHeader.h"

#include "Animation/AnimBlueprintGeneratedClass.h"
#include "Animation/AnimInstance.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "ContentBrowserDelegates.h"
#include "ContentBrowserModule.h"
#include "Editor.h"
#include "EditorStyleSet.h"
#include "Engine/Blueprint.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/SCS_Node.h"
#include "Engine/SimpleConstructionScript.h"
#include "FindInBlueprintManager.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "HAL/FileManager.h"
#include "HAL/IConsoleManager.h"
#include "IContentBrowserSingleton.h"
#include "IDetailsView.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Logging/LogMacros.h"
#include "Misc/MessageDialog.h"
#include "Misc/PackageName.h"
#include "Misc/ScopedSlowTask.h"
#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "ToolMenus.h"
#include "UObject/Package.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/UObjectHash.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SWindow.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Views/STableRow.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthBlueprintTools, Log, All);

namespace RebirthBlueprintToolsDetail
{
	const FName MenuOwner(TEXT("RebirthBlueprintTools"));
	FDelegateHandle GMenuStartup;
	FDelegateHandle GFolderMenuExtender;
	TUniquePtr<FAutoConsoleCommand> GWindowCommand;
	TUniquePtr<FAutoConsoleCommand> GChildCommand;

	struct FCachedHeader
	{
		FDateTime Modified;
		TArray<RebirthBlueprintTools::FGameBlueprint> Blueprints;
	};
	TMap<FString, FCachedHeader> GHeaderCache;

	bool IsGeneratedClassType(FName ClassName)
	{
		static const FName Types[] = { FName(TEXT("BlueprintGeneratedClass")), FName(TEXT("AnimBlueprintGeneratedClass")), FName(TEXT("WidgetBlueprintGeneratedClass")) };
		for (const FName& Type : Types)
		{
			if (ClassName == Type)
			{
				return true;
			}
		}
		return false;
	}

	void ReadBlueprints(const FString& Filename, const FString& PackageName, TArray<RebirthBlueprintTools::FGameBlueprint>& Out)
	{
		const FDateTime Modified = IFileManager::Get().GetTimeStamp(*Filename);
		if (const FCachedHeader* Cached = GHeaderCache.Find(Filename))
		{
			if (Cached->Modified == Modified)
			{
				Out.Append(Cached->Blueprints);
				return;
			}
		}
		FCachedHeader& Entry = GHeaderCache.FindOrAdd(Filename);
		Entry.Modified = Modified;
		Entry.Blueprints.Reset();
		RebirthPackageHeader::FHeader Header;
		FString Error;
		if (RebirthPackageHeader::Read(Filename, Header, true, Error) && Header.IsCooked())
		{
			for (int32 Index = 0; Index < Header.Exports.Num(); ++Index)
			{
				const RebirthPackageHeader::FExport& Export = Header.Exports[Index];
				const FName ClassType = Header.GetExportClassName(Index);
				if (Export.OuterIndex != 0 || !IsGeneratedClassType(ClassType))
				{
					continue;
				}
				RebirthBlueprintTools::FGameBlueprint& Blueprint = Entry.Blueprints.AddDefaulted_GetRef();
				Blueprint.PackageName = PackageName;
				Blueprint.ClassPath = PackageName + TEXT(".") + Export.ObjectName.ToString();
				Blueprint.GeneratedClassType = ClassType;
				if (Export.SuperIndex < 0)
				{
					Blueprint.ParentClassPath = Header.GetImportPath(-Export.SuperIndex - 1);
				}
				else if (Export.SuperIndex > 0 && Header.Exports.IsValidIndex(Export.SuperIndex - 1))
				{
					Blueprint.ParentClassPath = PackageName + TEXT(".") + Header.Exports[Export.SuperIndex - 1].ObjectName.ToString();
				}
			}
		}
		Out.Append(Entry.Blueprints);
	}

	void ShowDefaults(UClass* Class)
	{
		if (!Class)
		{
			return;
		}
		FPropertyEditorModule& PropertyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
		FDetailsViewArgs Args;
		Args.bAllowSearch = true;
		Args.bHideSelectionTip = true;
		Args.bShowOptions = true;
		Args.NameAreaSettings = FDetailsViewArgs::ObjectsUseNameArea;
		TSharedRef<IDetailsView> Details = PropertyEditor.CreateDetailView(Args);
		Details->SetIsPropertyEditingEnabledDelegate(FIsPropertyEditingEnabled::CreateLambda([]() { return false; }));

		// The class defaults, then every component template the blueprint adds.
		TArray<UObject*> Objects;
		Objects.Add(Class->GetDefaultObject());
		TArray<TSharedPtr<FString>>* Labels = new TArray<TSharedPtr<FString>>();
		Labels->Add(MakeShared<FString>(TEXT("Class defaults")));
		if (UBlueprintGeneratedClass* Generated = Cast<UBlueprintGeneratedClass>(Class))
		{
			if (Generated->SimpleConstructionScript)
			{
				for (USCS_Node* Node : Generated->SimpleConstructionScript->GetAllNodes())
				{
					if (Node && Node->ComponentTemplate)
					{
						Objects.Add(Node->ComponentTemplate);
						Labels->Add(MakeShared<FString>(FString::Printf(TEXT("Component: %s (%s)"), *Node->GetVariableName().ToString(), *Node->ComponentTemplate->GetClass()->GetName())));
					}
				}
			}
		}
		TSharedPtr<TArray<TSharedPtr<FString>>> Items(Labels);
		TArray<TWeakObjectPtr<UObject>> WeakObjects;
		for (UObject* Object : Objects)
		{
			WeakObjects.Add(Object);
		}
		Details->SetObject(Objects[0]);

		TSharedRef<SWindow> Window = SNew(SWindow)
			.Title(FText::FromString(FString::Printf(TEXT("%s (game blueprint, read-only)"), *Class->GetName())))
			.ClientSize(FVector2D(820.f, 760.f))
			[
				SNew(SBorder)
				.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
				.Padding(6.f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot().AutoWidth().Padding(0.f, 0.f, 6.f, 0.f)
					[
						SNew(SBox).WidthOverride(260.f)
						[
							SNew(SListView<TSharedPtr<FString>>)
							.ListItemsSource(Items.Get())
							.SelectionMode(ESelectionMode::Single)
							.OnGenerateRow_Lambda([Items](TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& Owner) -> TSharedRef<ITableRow>
							{
								return SNew(STableRow<TSharedPtr<FString>>, Owner)[SNew(STextBlock).Text(FText::FromString(*Item))];
							})
							.OnSelectionChanged_Lambda([Items, WeakObjects, Details](TSharedPtr<FString> Item, ESelectInfo::Type)
							{
								const int32 Index = Items->IndexOfByKey(Item);
								if (WeakObjects.IsValidIndex(Index) && WeakObjects[Index].IsValid())
								{
									Details->SetObject(WeakObjects[Index].Get());
								}
							})
						]
					]
					+ SHorizontalBox::Slot().FillWidth(1.f)
					[
						Details
					]
				]
			];
		FSlateApplication::Get().AddWindow(Window);
	}

	FString AskChildPackageName(UClass* Parent)
	{
		const FString ParentPackage = Parent->GetOutermost()->GetName();
		FString BaseName = Parent->GetName();
		BaseName.RemoveFromEnd(TEXT("_C"));
		FSaveAssetDialogConfig Config;
		Config.DialogTitleOverride = FText::FromString(FString::Printf(TEXT("Child blueprint of %s"), *BaseName));
		Config.DefaultPath = FPackageName::GetLongPackagePath(ParentPackage);
		Config.DefaultAssetName = BaseName + TEXT("_Child");
		Config.ExistingAssetPolicy = ESaveAssetDialogExistingAssetPolicy::Disallow;
		FContentBrowserModule& ContentBrowser = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
		const FString ObjectPath = ContentBrowser.Get().CreateModalSaveAssetDialog(Config);
		return ObjectPath.IsEmpty() ? FString() : FPackageName::ObjectPathToPackageName(ObjectPath);
	}

	void CreateChildWithDialog(const RebirthBlueprintTools::FGameBlueprint& Blueprint)
	{
		FString Error;
		UClass* Parent = RebirthBlueprintTools::LoadGameBlueprintClass(Blueprint.ClassPath, Error);
		if (!Parent)
		{
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("%s could not be loaded: %s"), *Blueprint.ClassPath, *Error)));
			return;
		}
		const FString PackageName = AskChildPackageName(Parent);
		if (PackageName.IsEmpty())
		{
			return;
		}
		UBlueprint* Child = RebirthBlueprintTools::CreateChildBlueprint(Parent, PackageName, Error);
		if (!Child)
		{
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Printf(TEXT("The child blueprint was not created: %s"), *Error)));
			return;
		}
		if (UAssetEditorSubsystem* Editors = GEditor ? GEditor->GetEditorSubsystem<UAssetEditorSubsystem>() : nullptr)
		{
			Editors->OpenEditorForAsset(Child);
		}
	}

	void OpenWindowForPaths(TArray<FString> Paths)
	{
		RebirthBlueprintTools::OpenGameBlueprintsWindow(Paths.Num() > 0 ? Paths[0] : FString());
	}

	TSharedRef<FExtender> ExtendFolderMenu(const TArray<FString>& SelectedPaths)
	{
		TSharedRef<FExtender> Extender = MakeShared<FExtender>();
		Extender->AddMenuExtension(TEXT("PathContextBulkOperations"), EExtensionHook::After, nullptr,
			FMenuExtensionDelegate::CreateLambda([SelectedPaths](FMenuBuilder& Menu)
			{
				Menu.AddMenuEntry(FText::FromString(TEXT("Rebirth: Game Blueprints in This Folder...")),
					FText::FromString(TEXT("List the game's blueprints in this folder: view their defaults and components, or create child blueprints from them.")),
					FSlateIcon(), FUIAction(FExecuteAction::CreateStatic(&OpenWindowForPaths, SelectedPaths)));
			}));
		return Extender;
	}

	void RegisterMenus()
	{
		FToolMenuOwnerScoped OwnerScoped(MenuOwner);
		if (UToolMenu* Menu = UToolMenus::Get()->ExtendMenu(TEXT("LevelEditor.MainMenu.File")))
		{
			FToolMenuSection& Section = Menu->FindOrAddSection(TEXT("RebirthDataObjects"));
			Section.Label = FText::FromString(TEXT("Rebirth"));
			Section.AddMenuEntry(TEXT("RebirthGameBlueprints"), FText::FromString(TEXT("Game Blueprints...")),
				FText::FromString(TEXT("The game's blueprints in this project: view their defaults and components, or create child blueprints (new characters and so on).")),
				FSlateIcon(), FUIAction(FExecuteAction::CreateLambda([]() { RebirthBlueprintTools::OpenGameBlueprintsWindow(); })));
		}
	}

	void RunWindowCommand(const TArray<FString>& Arguments)
	{
		RebirthBlueprintTools::OpenGameBlueprintsWindow(Arguments.Num() > 0 ? Arguments[0] : FString());
	}

	void RunChildCommand(const TArray<FString>& Arguments)
	{
		if (Arguments.Num() < 2)
		{
			UE_LOG(LogRebirthBlueprintTools, Display, TEXT("Usage: Rebirth.CreateChildBlueprint /Game/Path/GameBlueprint /Game/Path/NewChild"));
			return;
		}
		FString Error;
		UClass* Parent = RebirthBlueprintTools::LoadGameBlueprintClass(Arguments[0], Error);
		UBlueprint* Child = Parent ? RebirthBlueprintTools::CreateChildBlueprint(Parent, Arguments[1], Error) : nullptr;
		if (Child)
		{
			UE_LOG(LogRebirthBlueprintTools, Display, TEXT("Created %s (parent %s)."), *Child->GetPathName(), *Parent->GetPathName());
		}
		else
		{
			UE_LOG(LogRebirthBlueprintTools, Warning, TEXT("Not created: %s"), *Error);
		}
	}
}

namespace RebirthBlueprintTools
{
	using namespace RebirthBlueprintToolsDetail;

	void Register()
	{
		if (IsRunningCommandlet() || GMenuStartup.IsValid())
		{
			return;
		}
		GMenuStartup = UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateStatic(&RegisterMenus));
		FContentBrowserModule& ContentBrowser = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
		TArray<FContentBrowserMenuExtender_SelectedPaths>& Extenders = ContentBrowser.GetAllPathViewContextMenuExtenders();
		Extenders.Add(FContentBrowserMenuExtender_SelectedPaths::CreateStatic(&ExtendFolderMenu));
		GFolderMenuExtender = Extenders.Last().GetHandle();
		GWindowCommand = MakeUnique<FAutoConsoleCommand>(TEXT("Rebirth.GameBlueprints"),
			TEXT("List the game's blueprints in the project (optionally under a folder): Rebirth.GameBlueprints [/Game/BluePrint/Character]"),
			FConsoleCommandWithArgsDelegate::CreateStatic(&RunWindowCommand));
		GChildCommand = MakeUnique<FAutoConsoleCommand>(TEXT("Rebirth.CreateChildBlueprint"),
			TEXT("Create an editable child of a game blueprint: Rebirth.CreateChildBlueprint /Game/Path/GameBlueprint /Game/Path/NewChild"),
			FConsoleCommandWithArgsDelegate::CreateStatic(&RunChildCommand));
	}

	void Unregister()
	{
		if (GMenuStartup.IsValid())
		{
			UToolMenus::UnRegisterStartupCallback(GMenuStartup);
			GMenuStartup.Reset();
			if (UObjectInitialized() && !IsEngineExitRequested())
			{
				UToolMenus::UnregisterOwner(MenuOwner);
			}
		}
		if (GFolderMenuExtender.IsValid())
		{
			if (FContentBrowserModule* ContentBrowser = FModuleManager::GetModulePtr<FContentBrowserModule>(TEXT("ContentBrowser")))
			{
				ContentBrowser->GetAllPathViewContextMenuExtenders().RemoveAll([](const FContentBrowserMenuExtender_SelectedPaths& Delegate)
				{
					return Delegate.GetHandle() == GFolderMenuExtender;
				});
			}
			GFolderMenuExtender.Reset();
		}
		GWindowCommand.Reset();
		GChildCommand.Reset();
		GHeaderCache.Reset();
	}

	void FindGameBlueprints(const FString& Folder, TArray<FGameBlueprint>& OutBlueprints)
	{
		OutBlueprints.Reset();
		FString Root = Folder.IsEmpty() ? FString(TEXT("/Game")) : Folder;
		Root.RemoveFromEnd(TEXT("/"));
		FString Directory;
		if (!FPackageName::TryConvertLongPackageNameToFilename(Root + TEXT("/"), Directory))
		{
			return;
		}
		TArray<FString> Files;
		IFileManager::Get().FindFilesRecursive(Files, *Directory, TEXT("*.uasset"), true, false);
		for (const FString& File : Files)
		{
			FString PackageName;
			if (FPackageName::TryConvertFilenameToLongPackageName(File, PackageName))
			{
				ReadBlueprints(File, PackageName, OutBlueprints);
			}
		}
		OutBlueprints.Sort([](const FGameBlueprint& A, const FGameBlueprint& B) { return A.ClassPath < B.ClassPath; });
	}

	UClass* LoadGameBlueprintClass(const FString& ClassPathOrPackage, FString& OutError)
	{
		FString ClassPath = ClassPathOrPackage;
		const FString PackageName = FPackageName::ObjectPathToPackageName(ClassPathOrPackage);
		if (!ClassPath.Contains(TEXT(".")))
		{
			TArray<FGameBlueprint> Found;
			FString Filename;
			if (FPackageName::DoesPackageExist(PackageName, nullptr, &Filename))
			{
				ReadBlueprints(FPaths::ConvertRelativePathToFull(Filename), PackageName, Found);
			}
			if (Found.Num() == 0)
			{
				OutError = FString::Printf(TEXT("%s is not a cooked blueprint in this project"), *PackageName);
				return nullptr;
			}
			ClassPath = Found[0].ClassPath;
		}
		// Not loaded yet: its references to game assets that are not in the project become stand-ins first.
		if (!FindPackage(nullptr, *PackageName))
		{
			RebirthGameReferences::EnsureForPackage(PackageName);
		}
		UClass* Class = LoadObject<UClass>(nullptr, *ClassPath);
		if (!Class)
		{
			OutError = FString::Printf(TEXT("%s could not be loaded"), *ClassPath);
		}
		return Class;
	}

	UBlueprint* CreateChildBlueprint(UClass* ParentClass, const FString& PackageName, FString& OutError)
	{
		if (!ParentClass || !FKismetEditorUtilities::CanCreateBlueprintOfClass(ParentClass))
		{
			OutError = FString::Printf(TEXT("%s cannot be a blueprint parent"), *GetPathNameSafe(ParentClass));
			return nullptr;
		}
		FString Filename;
		if (!FPackageName::TryConvertLongPackageNameToFilename(PackageName, Filename, FPackageName::GetAssetPackageExtension()))
		{
			OutError = FString::Printf(TEXT("%s is not a valid content path"), *PackageName);
			return nullptr;
		}
		if (FPackageName::DoesPackageExist(PackageName) || FindPackage(nullptr, *PackageName))
		{
			OutError = FString::Printf(TEXT("%s already exists"), *PackageName);
			return nullptr;
		}
		if (ParentClass->IsChildOf(UAnimInstance::StaticClass()))
		{
			// A child anim blueprint compiles its own anim graph over the parent's, and the game's graph is not in the file.
			OutError = TEXT("child blueprints of the game's animation blueprints are not supported (their anim graph is compiled and not in the file)");
			return nullptr;
		}
		for (const UClass* Current = ParentClass; Current; Current = Current->GetSuperClass())
		{
			// A class the compiler can derive from is bound (it can construct objects) and has its defaults.
			if (Current->HasAnyFlags(RF_NeedLoad) || !Current->ClassConstructor || !Current->ClassWithin || !Current->GetDefaultObject(false))
			{
				OutError = FString::Printf(TEXT("%s (a parent of %s) is not completely loaded"), *Current->GetPathName(), *ParentClass->GetPathName());
				return nullptr;
			}
		}
		// The blueprint search index builds itself on first use (in a commandlet: in the first compile) from every blueprint
		// in memory, asking each for its class defaults; the new blueprint's class cannot make them before it is compiled.
		// Build the index before the new blueprint exists.
		FFindInBlueprintSearchManager::Get();

		UPackage* Package = CreatePackage(*PackageName);
		// Everything of a new package is in memory (otherwise it stops counting as fully loaded once its file exists).
		Package->MarkAsFullyLoaded();
		const FName Name(*FPackageName::GetLongPackageAssetName(PackageName));
		UBlueprint* Blueprint = FKismetEditorUtilities::CreateBlueprint(ParentClass, Package, Name, BPTYPE_Normal,
			UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), FName(TEXT("RebirthChildBlueprint")));
		if (!Blueprint)
		{
			OutError = TEXT("the blueprint could not be created");
			return nullptr;
		}
		FAssetRegistryModule::AssetCreated(Blueprint);
		Package->MarkPackageDirty();
		Filename = FPaths::ConvertRelativePathToFull(Filename);
		if (!UPackage::SavePackage(Package, Blueprint, RF_Public | RF_Standalone, *Filename, GError, nullptr, false, true, SAVE_NoError))
		{
			OutError = FString::Printf(TEXT("the blueprint was created but saving %s failed"), *Filename);
			return Blueprint;
		}
		if (Blueprint->Status == BS_Error)
		{
			UE_LOG(LogRebirthBlueprintTools, Warning, TEXT("%s was created but does not compile; open it to see the errors."), *Blueprint->GetPathName());
		}
		UE_LOG(LogRebirthBlueprintTools, Display, TEXT("Created child blueprint %s of %s."), *Blueprint->GetPathName(), *ParentClass->GetPathName());
		return Blueprint;
	}

	void OpenGameBlueprintsWindow(const FString& Folder)
	{
		if (!FSlateApplication::IsInitialized())
		{
			return;
		}
		struct FState
		{
			TArray<FGameBlueprint> Blueprints;
			TArray<TSharedPtr<FGameBlueprint>> All;
			TArray<TSharedPtr<FGameBlueprint>> Shown;
			TSharedPtr<SListView<TSharedPtr<FGameBlueprint>>> List;
			FString Filter;

			void Refresh()
			{
				Shown.Reset();
				for (const TSharedPtr<FGameBlueprint>& Item : All)
				{
					if (Filter.IsEmpty() || Item->ClassPath.Contains(Filter) || Item->ParentClassPath.Contains(Filter))
					{
						Shown.Add(Item);
					}
				}
				if (List.IsValid())
				{
					List->RequestListRefresh();
				}
			}

			TSharedPtr<FGameBlueprint> Selected() const
			{
				const TArray<TSharedPtr<FGameBlueprint>> Items = List.IsValid() ? List->GetSelectedItems() : TArray<TSharedPtr<FGameBlueprint>>();
				return Items.Num() > 0 ? Items[0] : nullptr;
			}
		};
		TSharedRef<FState> State = MakeShared<FState>();
		{
			FScopedSlowTask Task(1.f, FText::FromString(TEXT("Finding the game's blueprints in this project")));
			Task.MakeDialog();
			Task.EnterProgressFrame(1.f);
			FindGameBlueprints(Folder, State->Blueprints);
		}
		for (const FGameBlueprint& Blueprint : State->Blueprints)
		{
			State->All.Add(MakeShared<FGameBlueprint>(Blueprint));
		}
		State->Shown = State->All;

		const FString Title = FString::Printf(TEXT("Game Blueprints in %s (%d)"), Folder.IsEmpty() ? TEXT("/Game") : *Folder, State->All.Num());
		TSharedRef<SWindow> Window = SNew(SWindow)
			.Title(FText::FromString(Title))
			.ClientSize(FVector2D(900.f, 620.f))
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
						.Text(FText::FromString(TEXT("Blueprints copied from the game are classes without graphs, so the content browser cannot show them. ")
							TEXT("View one to see its defaults and components, or create a child blueprint: an editable blueprint that inherits everything from the game's class. ")
							TEXT("Override defaults and components (mesh, materials, anim class...) and add your own nodes; Package Project cooks it like any blueprint.")))
					]
					+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 0.f, 0.f, 6.f)
					[
						SNew(SSearchBox)
						.OnTextChanged_Lambda([State](const FText& Text) { State->Filter = Text.ToString(); State->Refresh(); })
					]
					+ SVerticalBox::Slot().FillHeight(1.f)
					[
						SAssignNew(State->List, SListView<TSharedPtr<FGameBlueprint>>)
						.ListItemsSource(&State->Shown)
						.SelectionMode(ESelectionMode::Single)
						.OnGenerateRow_Lambda([](TSharedPtr<FGameBlueprint> Item, const TSharedRef<STableViewBase>& Owner) -> TSharedRef<ITableRow>
						{
							FString Parent = Item->ParentClassPath;
							int32 Dot = INDEX_NONE;
							if (Parent.FindLastChar(TEXT('.'), Dot))
							{
								Parent = Parent.Mid(Dot + 1);
							}
							return SNew(STableRow<TSharedPtr<FGameBlueprint>>, Owner)
							[
								SNew(STextBlock).Text(FText::FromString(FString::Printf(TEXT("%s    (parent %s)"), *Item->PackageName, *Parent)))
							];
						})
						.OnMouseButtonDoubleClick_Lambda([](TSharedPtr<FGameBlueprint> Item)
						{
							FString Error;
							if (Item.IsValid())
							{
								RebirthBlueprintToolsDetail::ShowDefaults(LoadGameBlueprintClass(Item->ClassPath, Error));
							}
						})
					]
					+ SVerticalBox::Slot().AutoHeight().HAlign(HAlign_Right).Padding(0.f, 6.f, 0.f, 0.f)
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().AutoWidth().Padding(0.f, 0.f, 6.f, 0.f)
						[
							SNew(SButton)
							.Text(FText::FromString(TEXT("View Defaults")))
							.OnClicked_Lambda([State]()
							{
								if (TSharedPtr<FGameBlueprint> Item = State->Selected())
								{
									FString Error;
									UClass* Class = LoadGameBlueprintClass(Item->ClassPath, Error);
									if (Class)
									{
										RebirthBlueprintToolsDetail::ShowDefaults(Class);
									}
									else
									{
										FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Error));
									}
								}
								return FReply::Handled();
							})
						]
						+ SHorizontalBox::Slot().AutoWidth()
						[
							SNew(SButton)
							.Text(FText::FromString(TEXT("Create Child Blueprint...")))
							.OnClicked_Lambda([State]()
							{
								if (TSharedPtr<FGameBlueprint> Item = State->Selected())
								{
									RebirthBlueprintToolsDetail::CreateChildWithDialog(*Item);
								}
								return FReply::Handled();
							})
						]
					]
				]
			];
		FSlateApplication::Get().AddWindow(Window);
	}
}
