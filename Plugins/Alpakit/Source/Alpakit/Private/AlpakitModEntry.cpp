#include "AlpakitModEntry.h"
#include "Alpakit.h"
#include "AlpakitSettings.h"
#include "AlpakitStyle.h"
#include "ISourceControlModule.h"
#include "ISourceControlProvider.h"
#include "ISourceControlOperation.h"
#include "ModMetadataObject.h"
#include "SourceControlOperations.h"
#include "Async/Async.h"
#include "UATHelper/Public/IUATHelperModule.h"
#include "FileHelpers.h"
#include "ISettingsModule.h"
#include "Settings/ProjectPackagingSettings.h"

#define LOCTEXT_NAMESPACE "AlpakitModListEntry"

void SAlpakitModEntry::Construct(const FArguments &Args, TSharedRef<IPlugin> InMod, TSharedRef<SAlpakitModEntryList> InOwner)
{
    Mod = InMod;
    Owner = InOwner;

    UAlpakitSettings *Settings = UAlpakitSettings::Get();
    const FString PluginName = Mod->GetName();

    Checkbox = SNew(SCheckBox)
                   .OnCheckStateChanged(this, &SAlpakitModEntry::OnEnableCheckboxChanged)
                   .IsChecked(Settings->ModSelection.FindOrAdd(PluginName, false));

    ChildSlot[SNew(SHorizontalBox) + SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 5, 0).VAlign(VAlign_Center)[Checkbox.ToSharedRef()] + SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 5, 0).VAlign(VAlign_Center)[SNew(SButton).Text(LOCTEXT("PackageModAlpakit", "Alpakit!")).OnClicked_Lambda([this]()
                                                                                                                                                                                                                                                                                                       {
                PackageMod(TArray<TSharedPtr<SAlpakitModEntry>>());
                return FReply::Handled(); })
                                                                                                                                                                                                                             .ToolTipText_Lambda([this]()
                                                                                                                                                                                                                                                 { return FText::FromString(FString::Printf(TEXT("Alpakit %s"), *this->Mod->GetName())); })] +
              SHorizontalBox::Slot().AutoWidth().Padding(0, 0, 5, 0).VAlign(VAlign_Center)[SNew(SButton).Text(LOCTEXT("EditModAlpakit", "Edit")).OnClicked_Lambda([this]()
                                                                                                                                                                  {
				this->OnEditMod();
                return FReply::Handled(); })
                                                                                               .ToolTipText_Lambda([this]()
                                                                                                                   { return FText::FromString(FString::Printf(TEXT("Edit %s"), *this->Mod->GetName())); })] +
              SHorizontalBox::Slot().FillWidth(1).VAlign(VAlign_Center)[SNew(STextBlock)
                                                                            .Text_Lambda([InMod]()
                                                                                         {
                const FString DisplayText = FString::Printf(TEXT("%s (%s)"), *InMod->GetDescriptor().FriendlyName, *InMod->GetName());
                return FText::FromString(DisplayText); })
                                                                            .HighlightText_Lambda([InOwner]()
                                                                                                  { return FText::FromString(InOwner->GetLastFilter()); })]];
}
void SAlpakitModEntry::OnEditMod()
{
    // Construct the plugin metadata object using the descriptor for this plugin
    UModMetadataObject *MetadataObject = NewObject<UModMetadataObject>();
    MetadataObject->TargetIconPath = Mod->GetBaseDir() / TEXT("Resources/Icon128.png");
    MetadataObject->PopulateFromDescriptor(Mod->GetDescriptor());
    MetadataObject->AddToRoot();

    // Create a property view
    FPropertyEditorModule &EditModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
    EditModule.RegisterCustomClassLayout(UModMetadataObject::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FModMetadataCustomization::MakeInstance));
    TSharedRef<IDetailsView> PropertyView = EditModule.CreateDetailView(FDetailsViewArgs(false, false, false, FDetailsViewArgs::ActorsUseNameArea, true));
    PropertyView->SetObject(MetadataObject, true);

    // Create the window
    PropertiesWindow = SNew(SWindow)
                           .ClientSize(FVector2D(800.0f, 700.0f))
                           .Title(LOCTEXT("ModMetadata", "Mod Properties"))
                           .Content()
                               [SNew(SBorder)
                                    .Padding(FMargin(8.0f, 8.0f))
                                        [SNew(SVerticalBox)

                                         + SVerticalBox::Slot()
                                               .AutoHeight()
                                               .Padding(FMargin(5.0f, 10.0f, 5.0f, 5.0f))
                                                   [SNew(STextBlock)
                                                        .Text(FText::FromString(Mod->GetName()))]

                                         + SVerticalBox::Slot()
                                               .Padding(5)
                                                   [PropertyView]

                                         + SVerticalBox::Slot()
                                               .AutoHeight()
                                               .Padding(5)
                                               .HAlign(HAlign_Right)
                                                   [SNew(SButton)
                                                        .ContentPadding(FMargin(20.0f, 2.0f))
                                                        .Text(LOCTEXT("OkButtonLabel", "Ok"))
                                                        .OnClicked(this, &SAlpakitModEntry::OnEditModFinished, MetadataObject)]]];

    FSlateApplication::Get().AddModalWindow(PropertiesWindow.ToSharedRef(), Owner);
}

FReply SAlpakitModEntry::OnEditModFinished(UModMetadataObject *MetadataObject)
{
    FPluginDescriptor OldDescriptor = Mod->GetDescriptor();

    // Update the descriptor with the new metadata
    FPluginDescriptor NewDescriptor = OldDescriptor;
    MetadataObject->CopyIntoDescriptor(NewDescriptor);
    MetadataObject->RemoveFromRoot();

    // Close the properties window
    PropertiesWindow->RequestDestroyWindow();

    // Write both to strings
    FString OldText;
    OldDescriptor.Write(OldText);
    FString NewText;
    NewDescriptor.Write(NewText);
    if (OldText.Compare(NewText, ESearchCase::CaseSensitive) != 0)
    {
        FString DescriptorFileName = Mod->GetDescriptorFileName();

        // First attempt to check out the file if SCC is enabled
        ISourceControlModule &SourceControlModule = ISourceControlModule::Get();
        if (SourceControlModule.IsEnabled())
        {
            ISourceControlProvider &SourceControlProvider = SourceControlModule.GetProvider();
            TSharedPtr<ISourceControlState, ESPMode::ThreadSafe> SourceControlState = SourceControlProvider.GetState(DescriptorFileName, EStateCacheUsage::ForceUpdate);
            if (SourceControlState.IsValid() && SourceControlState->CanCheckout())
            {
                SourceControlProvider.Execute(ISourceControlOperation::Create<FCheckOut>(), DescriptorFileName);
            }
        }

        // Write to the file and update the in-memory metadata
        FText FailReason;
        if (!Mod->UpdateDescriptor(NewDescriptor, FailReason))
        {
            FMessageDialog::Open(EAppMsgType::Ok, FailReason);
        }
    }
    return FReply::Handled();
}

FString GetArgumentForLaunchType(EAlpakitStartGameType LaunchMode)
{
    switch (LaunchMode) {
    case EAlpakitStartGameType::STEAM:
        return TEXT("Steam");
    case EAlpakitStartGameType::EPIC:
        return TEXT("Epic");
    default:
        return TEXT("None");
    }
}

FText GetCurrentPlatformName()
{
#if PLATFORM_WINDOWS
    return LOCTEXT("PlatformName_Windows", "Windows");
#elif PLATFORM_MAC
    return LOCTEXT("PlatformName_Mac", "Mac");
#elif PLATFORM_LINUX
    return LOCTEXT("PlatformName_Linux", "Linux");
#else
    return LOCTEXT("PlatformName_Other", "Other OS");
#endif
}

void SAlpakitModEntry::SaveDirtyPackages() const
{
    TArray<UPackage*> DirtyPackages;

    // Iterate over all loaded packages
    for (UPackage* Package : TObjectRange<UPackage>())
    {
        if (Package && Package->IsDirty() && !Package->HasAnyFlags(RF_Transient))
        {
            DirtyPackages.Add(Package);
        }
    }

    if (DirtyPackages.Num() > 0)
    {
        UEditorLoadingAndSavingUtils::SavePackages(DirtyPackages, true);
    }
}


void SAlpakitModEntry::SetNeverCookDirectoriesForMod(const TSharedPtr<IPlugin>& CurrentModPlugin) const
{
    UProjectPackagingSettings* PackagingSettings = GetMutableDefault<UProjectPackagingSettings>();

    // Clear all existing never-cook directories
    PackagingSettings->DirectoriesToNeverCook.Empty();

    // Add game content directory ("/Game")
    {
        FDirectoryPath GameDir;
        GameDir.Path = TEXT("/Game");
        PackagingSettings->DirectoriesToNeverCook.Add(GameDir);
    }

    // Project's /Mods/ folder on disk
    const FString ModsRootPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / TEXT("Mods/"));

    // Loop through all discovered plugins
    TArray<TSharedRef<IPlugin>> AllPlugins = IPluginManager::Get().GetDiscoveredPlugins();
    for (const TSharedRef<IPlugin>& Plugin : AllPlugins)
    {
        if (Plugin != CurrentModPlugin && Plugin->CanContainContent())
        {
            const FString PluginFilePath = FPaths::ConvertRelativePathToFull(Plugin->GetDescriptorFileName());

            // Only include plugins located inside the Mods directory
            if (PluginFilePath.StartsWith(ModsRootPath))
            {
                const FString ContentMountPath = Plugin->GetMountedAssetPath(); // e.g. "/ModName/"
                if (!ContentMountPath.IsEmpty())
                {
                    FDirectoryPath PluginDir;
                    PluginDir.Path = ContentMountPath.LeftChop(1); // Strip trailing slash
                    PackagingSettings->DirectoriesToNeverCook.Add(PluginDir);
                }
            }
        }
    }

    PackagingSettings->UpdateDefaultConfigFile(); // Save to config
}

void SAlpakitModEntry::PackageMod(const TArray<TSharedPtr<SAlpakitModEntry>> &NextEntries) const
{
    // Set DirectoriesToNeverCook
    SaveDirtyPackages();
    SetNeverCookDirectoriesForMod(Mod);

    UAlpakitSettings *Settings = UAlpakitSettings::Get();
    const FString PluginName = Mod->GetName();
    const FString GamePath = Settings->FF7RGamePath.Path;

    const FString ProjectPath = FPaths::IsProjectFilePathSet()
                                    ? FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath())
                                    : FPaths::RootDir() / FApp::GetProjectName() / FApp::GetProjectName() + TEXT(".uproject");

    FString AdditionalUATArguments;
    /*if (Settings->bCopyModsToGame)
    {
        AdditionalUATArguments.Append(TEXT("-CopyToGameDir "));
    }
    if (Settings->LaunchGameAfterPacking != EAlpakitStartGameType::NONE && NextEntries.Num() == 0)
    {
        AdditionalUATArguments.Append(TEXT("-LaunchGame "));
        AdditionalUATArguments.Append(GetArgumentForLaunchType(Settings->LaunchGameAfterPacking)).Append(TEXT(" "));
    }*/

    const FString LaunchGameArgument = GetArgumentForLaunchType(Settings->LaunchGameAfterPacking);

    UE_LOG(LogAlpakit, Display, TEXT("Packaging plugin \"%s\". %d remaining"), *PluginName, NextEntries.Num());


    EBuildConfiguration BuildConfiguration = EBuildConfiguration::Shipping;

    FString CommandLine = FString::Printf(TEXT("-ScriptsForProject=\"%s\" PackagePlugin -Project=\"%s\" -DLCName=\"%s\" -clientconfig=%s -utf8output %s"),
                                                *ProjectPath, *ProjectPath, *PluginName, LexToString(BuildConfiguration),*AdditionalUATArguments);

    if (bBuild) {
        CommandLine += TEXT(" -build");
    }

    if (Settings->bCopyModsToGame)
    {
        CommandLine += FString::Printf(TEXT(" -CopyToGameDirectory_WindowsNoEditor=\"%s\""), *GamePath);
    }
    if (NextEntries.Num() == 0)
    {
        CommandLine += FString::Printf(TEXT(" -LaunchGame_WindowsNoEditor=%s"), *LaunchGameArgument);
    }
    else
        CommandLine += FString::Printf(TEXT(" -LaunchGame_WindowsNoEditor=None"));


    CommandLine += GIsEditor || FApp::IsEngineInstalled() ? TEXT(" -nocompileeditor") : TEXT("");
    CommandLine += FApp::IsEngineInstalled() ? TEXT(" -installed") : TEXT("");
    //CommandLine += TEXT(" -nobuild");

    CommandLine += bMergeArchive ? TEXT(" -merge") : TEXT("");
   

    IUATHelperModule::UatTaskResultCallack OnUatCompleted;

    if (NextEntries.Num() == 0)
    {
        OnUatCompleted = [Mod = this->Mod](FString ResultType, double RunTime)
        {
            AsyncTask(ENamedThreads::GameThread, [Mod]()
                {
                    UE_LOG(LogAlpakit, Display, TEXT("Clearing DirectoriesToNeverCook."));

                    UProjectPackagingSettings* PackagingSettings = GetMutableDefault<UProjectPackagingSettings>();
                    PackagingSettings->DirectoriesToNeverCook.Empty();
                });
        };
    }
    else
    {
        OnUatCompleted = [NextEntries](FString ResultType, double RunTime)
        {
            AsyncTask(ENamedThreads::GameThread, [NextEntries]()
                {
                    TSharedPtr<SAlpakitModEntry> NextMod = NextEntries[0];

                    TArray<TSharedPtr<SAlpakitModEntry>> RemainingEntries = NextEntries.FilterByPredicate([NextMod](const TSharedPtr<SAlpakitModEntry>& X) {
                        return X != NextMod;
                        });

                    NextMod->PackageMod(RemainingEntries);
                });
        };
    }


    const FText PlatformName = GetCurrentPlatformName();
    IUATHelperModule::Get().CreateUatTask(
        CommandLine,
        PlatformName,
        LOCTEXT("PackageModTaskName", "Packaging Mod"),
        LOCTEXT("PackageModTaskShortName", "Package Mod Task"),
        // REQ Engine Update
        // FAlpakitStyle::Get().GetBrush("Alpakit.OpenPluginWindow"),
        nullptr,
        OnUatCompleted
    );
}

void SAlpakitModEntry::OnEnableCheckboxChanged(ECheckBoxState NewState)
{
    // Save new checked state for the mod at the
    UAlpakitSettings *Settings = UAlpakitSettings::Get();
    const FString PluginName = Mod->GetName();

    Settings->ModSelection.Add(PluginName, NewState == ECheckBoxState::Checked);

    Settings->SaveSettings();
}

#undef LOCTEXT_NAMESPACE
