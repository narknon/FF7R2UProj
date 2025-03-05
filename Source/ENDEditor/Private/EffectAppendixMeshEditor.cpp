#include "EffectAppendixMeshEditor.h"
#include "SEffectAppendixMeshEditorViewport.h"
#include "EffectAppendixMesh.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "EditorStyleSet.h"
#include "Editor/UnrealEdEngine.h"
#include "UnrealEdGlobals.h"
#include "Components/StaticMeshComponent.h"
#include "AssetEditorModeManager.h"
#include "CanvasTypes.h"
#include "Materials/Material.h"
#include "Framework/Docking/TabManager.h"
#include "Widgets/Docking/SDockTab.h"
#include "SEditorViewport.h"

const FName FEffectAppendixMeshEditor::ViewportTabId(TEXT("EffectAppendixMeshEditor_Viewport"));
const FName FEffectAppendixMeshEditor::DetailsTabId(TEXT("EffectAppendixMeshEditor_Details"));

#define LOCTEXT_NAMESPACE "EffectAppendixMeshEditor"

void FEffectAppendixMeshEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
    WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_EffectAppendixMeshEditor", "Effect Appendix Mesh Editor"));
    auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

    FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
    
    InTabManager->RegisterTabSpawner(ViewportTabId, FOnSpawnTab::CreateSP(this, &FEffectAppendixMeshEditor::SpawnTab_Viewport))
        .SetDisplayName(LOCTEXT("ViewportTab", "Viewport"))
        .SetGroup(WorkspaceMenuCategoryRef)
        .SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports"));
    
    InTabManager->RegisterTabSpawner(DetailsTabId, FOnSpawnTab::CreateSP(this, &FEffectAppendixMeshEditor::SpawnTab_Details))
        .SetDisplayName(LOCTEXT("DetailsTab", "Details"))
        .SetGroup(WorkspaceMenuCategoryRef)
        .SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));
}

void FEffectAppendixMeshEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
    InTabManager->UnregisterTabSpawner(ViewportTabId);
    InTabManager->UnregisterTabSpawner(DetailsTabId);
    
    FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
}

FName FEffectAppendixMeshEditor::GetToolkitFName() const
{
    return FName("EffectAppendixMeshEditor");
}

FText FEffectAppendixMeshEditor::GetBaseToolkitName() const
{
    return LOCTEXT("AppLabel", "Effect Appendix Mesh Editor");
}

FString FEffectAppendixMeshEditor::GetWorldCentricTabPrefix() const
{
    return LOCTEXT("WorldCentricTabPrefix", "Effect Appendix Mesh ").ToString();
}

FLinearColor FEffectAppendixMeshEditor::GetWorldCentricTabColorScale() const
{
    return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}

void FEffectAppendixMeshEditor::AddReferencedObjects(FReferenceCollector& Collector)
{
    Collector.AddReferencedObject(EffectAppendixMesh);
}

void FEffectAppendixMeshEditor::InitEffectAppendixMeshEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UEffectAppendixMesh* InEffectAppendixMesh)
{
    EffectAppendixMesh = InEffectAppendixMesh;

    // Create a details view
    FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
    const FDetailsViewArgs DetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, true);
    DetailsWidget = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
    
    // Set callback for property changes
    DetailsWidget->OnFinishedChangingProperties().AddRaw(this, &FEffectAppendixMeshEditor::OnPropertiesChanged);
    
    // Set the object to the details panel
    DetailsWidget->SetObject(EffectAppendixMesh);

    // Create the viewport
    ViewportWidget = SNew(SEffectAppendixMeshEditorViewport, SharedThis(this));
    ViewportWidget->SetEffectAppendixMesh(EffectAppendixMesh);

    // Set up the tabs
    const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_EffectAppendixMeshEditor_Layout_v1")
        ->AddArea
        (
            FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
            ->Split
            (
                FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)->SetSizeCoefficient(0.9f)
                ->Split
                (
                    FTabManager::NewStack()
                    ->AddTab(ViewportTabId, ETabState::OpenedTab)->SetHideTabWell(true)
                    ->SetSizeCoefficient(0.7f)
                )
                ->Split
                (
                    FTabManager::NewStack()
                    ->AddTab(DetailsTabId, ETabState::OpenedTab)
                    ->SetSizeCoefficient(0.3f)
                )
            )
        );

    // Initialize the asset editor
    InitAssetEditor(Mode, InitToolkitHost, FName("EffectAppendixMeshEditorApp"), StandaloneDefaultLayout, true, true, InEffectAppendixMesh);
    
    // Update preview mesh
    if (EffectAppendixMesh)
    {
        EffectAppendixMesh->CreatePreviewMesh();
    }
}

TSharedRef<SDockTab> FEffectAppendixMeshEditor::SpawnTab_Viewport(const FSpawnTabArgs& Args)
{
    return SNew(SDockTab)
        .Label(LOCTEXT("ViewportTitle", "Viewport"))
        [
            ViewportWidget.ToSharedRef()
        ];
}

TSharedRef<SDockTab> FEffectAppendixMeshEditor::SpawnTab_Details(const FSpawnTabArgs& Args)
{
    return SNew(SDockTab)
        .Label(LOCTEXT("DetailsTitle", "Details"))
        [
            DetailsWidget.ToSharedRef()
        ];
}

void FEffectAppendixMeshEditor::OnPropertiesChanged(const FPropertyChangedEvent& PropertyChangedEvent)
{
    if (!EffectAppendixMesh)
        return;
        
    // Check if we need to update the animation timing
    if (PropertyChangedEvent.Property && 
        (PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UEffectAppendixMesh, EditorTotalTime) ||
         PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UEffectAppendixMesh, AnimationPlaybackSpeed)))
    {
        // Apply the properties to the asset immediately
        EffectAppendixMesh->ApplyEditorValuesToAsset();
        
        // Update the timing display in the viewport
        if (ViewportWidget.IsValid())
        {
            ViewportWidget->UpdateAnimationTiming();
        }
        
        // Force redraw viewports
        if (GEditor)
        {
            GEditor->RedrawAllViewports();
        }
    }
}

#undef LOCTEXT_NAMESPACE