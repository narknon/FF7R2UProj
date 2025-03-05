#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "EditorViewportClient.h"
#include "SEditorViewport.h"
#include "EffectAppendixMesh.h"

class FEffectAppendixMeshEditor : public FAssetEditorToolkit, public FGCObject
{
public:
    FEffectAppendixMeshEditor(): EffectAppendixMesh(nullptr)
    {
    }

    virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
    virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;

    // FAssetEditorToolkit
    virtual FName GetToolkitFName() const override;
    virtual FText GetBaseToolkitName() const override;
    virtual FString GetWorldCentricTabPrefix() const override;
    virtual FLinearColor GetWorldCentricTabColorScale() const override;
    
    // FGCObject interface
    virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
    virtual FString GetReferencerName() const override { return TEXT("FEffectAppendixMeshEditor"); }

    // Initializes the asset editor
    void InitEffectAppendixMeshEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UEffectAppendixMesh* InEffectAppendixMesh);

    // Get the asset being edited
    UEffectAppendixMesh* GetEffectAppendixMeshBeingEdited() const { return EffectAppendixMesh; }

    // Called when the editor properties are updated
    void OnPropertiesChanged(const FPropertyChangedEvent& PropertyChangedEvent);

private:
    // Create widget for the viewport
    TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);
    TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);

private:
    // The effect appendix mesh asset being edited
    UEffectAppendixMesh* EffectAppendixMesh;
    
    // Viewport widget
    TSharedPtr<class SEffectAppendixMeshEditorViewport> ViewportWidget;
    
    // Details view
    TSharedPtr<class IDetailsView> DetailsWidget;
    
    // Tab IDs
    static const FName ViewportTabId;
    static const FName DetailsTabId;
};