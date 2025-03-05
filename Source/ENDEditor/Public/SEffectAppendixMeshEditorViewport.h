#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "EditorViewportClient.h"
#include "SEditorViewport.h"
#include "EffectAppendixMesh.h"

/**
 * Viewport client for the EffectAppendixMesh editor
 */
class FEffectAppendixMeshEditorViewportClient : public FEditorViewportClient
{
public:
    FEffectAppendixMeshEditorViewportClient(FPreviewScene& InPreviewScene, const TWeakPtr<class SEditorViewport>& InViewportWidget = nullptr);
    virtual ~FEffectAppendixMeshEditorViewportClient();

    // FEditorViewportClient interface
    virtual void Tick(float DeltaSeconds) override;
    virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;
    virtual void DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas) override;

    // Sets the effect appendix mesh to preview
    void SetEffectAppendixMesh(UEffectAppendixMesh* InEffectAppendixMesh);
    
    // Animation control
    void StartAnimation();
    void PauseAnimation();
    void StopAnimation();
    void SetPlaybackSpeed(float Speed);
    void DrawMeshWireframe(FPrimitiveDrawInterface* PDI);
    void DrawAnimatedVertices(FPrimitiveDrawInterface* PDI);
    
    bool IsPlaying() const { return bIsPlaying; }
    
    // Get the current animation time (normalized 0-1)
    float GetCurrentAnimationTime() const { return CurrentAnimTime; }
    
    // Set the current animation time directly (normalized 0-1)
    void SetCurrentAnimationTime(float Time);
    
    // The effect appendix mesh being previewed
    TWeakObjectPtr<UEffectAppendixMesh> EffectAppendixMesh;
    
    // Cached mesh component for preview
    TWeakObjectPtr<UStaticMeshComponent> MeshComponent;
    
    // Animation state
    bool bIsPlaying;
    float CurrentAnimTime;      // Normalized 0-1 animation time
    float PlaybackSpeed;        // Speed multiplier
    float TotalAnimationTime;   // Total animation time in seconds
};

/**
 * Viewport for editing and previewing an EffectAppendixMesh
 */
class SEffectAppendixMeshEditorViewport : public SEditorViewport
{
public:
    SLATE_BEGIN_ARGS(SEffectAppendixMeshEditorViewport) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs, TSharedPtr<class FEffectAppendixMeshEditor> InEffectAppendixMeshEditor);
    ~SEffectAppendixMeshEditorViewport();

    // SEditorViewport interface
    virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
    
    // Sets the effect appendix mesh to preview
    void SetEffectAppendixMesh(UEffectAppendixMesh* InEffectAppendixMesh);
    
    // Animation controls
    void OnPlayClicked();
    void OnPauseClicked();
    void OnStopClicked();
    void OnScrubValueChanged(float NewValue);
    void UpdateAnimationTiming();

protected:
    // SEditorViewport interface
    virtual TSharedPtr<SWidget> MakeViewportToolbar() override;

private:
    // Pointer back to the effect appendix mesh editor tool that owns us
    TWeakPtr<class FEffectAppendixMeshEditor> EffectAppendixMeshEditorPtr;
    
    // Viewport client
    TSharedPtr<FEffectAppendixMeshEditorViewportClient> EditorViewportClient;
    
    // The preview scene
    FPreviewScene PreviewScene;
    
    // UI Elements
    TSharedPtr<class SSlider> TimelineSlider;
    TSharedPtr<class STextBlock> TimeText;
};