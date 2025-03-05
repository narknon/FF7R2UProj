#include "SEffectAppendixMeshEditorViewport.h"
#include "EffectAppendixMeshEditor.h"
#include "EffectAppendixMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Editor/UnrealEdEngine.h"
#include "UnrealEdGlobals.h"
#include "EditorViewportClient.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Input/SSlider.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "EditorStyleSet.h"

//////////////////////////////////////////////////////////////////////////
// FEffectAppendixMeshEditorViewportClient

FEffectAppendixMeshEditorViewportClient::FEffectAppendixMeshEditorViewportClient(FPreviewScene& InPreviewScene, const TWeakPtr<class SEditorViewport>& InViewportWidget)
    : FEditorViewportClient(nullptr, &InPreviewScene, InViewportWidget)
    , bIsPlaying(false)
    , CurrentAnimTime(0.0f)
    , PlaybackSpeed(1.0f)
    , TotalAnimationTime(1.0f)
{
    // Setup defaults
    SetViewMode(VMI_Lit);
    
    // Set the default view rotation/location
    SetViewLocation(FVector(0.0f, 0.0f, 200.0f));
    SetViewRotation(FRotator(-45.0f, 0.0f, 0.0f));
    
    EngineShowFlags.SetGrid(true);
    EngineShowFlags.SetDirectionalLights(true);
    /*EngineShowFlags.SetEnvironmentLighting(true);*/
    EngineShowFlags.SetSkyLighting(true);
    
    // Don't want to display widget manipulators
    /*Widget->SetEnabled(false);*/
    
    // Always show scrollbars
    /*ShowScrollbars();*/
    
    // Always draw the translucent selection outline
    EngineShowFlags.SetSelection(true);
    EngineShowFlags.SetSelectionOutline(true);
    
    // Update the preview scene light colors to match the editor preferences
    /*PreviewScene->UpdateDefaultLighting();*/
    
    // Always refresh when scene is modified
    SetRealtime(true);
}

FEffectAppendixMeshEditorViewportClient::~FEffectAppendixMeshEditorViewportClient()
{
}

void FEffectAppendixMeshEditorViewportClient::Tick(float DeltaSeconds)
{
    FEditorViewportClient::Tick(DeltaSeconds);
    
    // Update animation time if playing
    if (bIsPlaying && EffectAppendixMesh.IsValid())
    {
        // Get the playback speed from the asset
        float Speed = EffectAppendixMesh->AnimationPlaybackSpeed;
        if (Speed <= 0.0f) Speed = 1.0f; // Ensure we have a valid speed
        
        // Get total animation time from the asset
        float TotalAnimationTime = EffectAppendixMesh->GetTotalAnimationTimeInSeconds();
        if (TotalAnimationTime <= 0.1f) TotalAnimationTime = 1.0f; // Ensure we have a valid time
        
        // Update the animation time with the proper speed factor
        CurrentAnimTime += DeltaSeconds * Speed / TotalAnimationTime;
        
        // Loop if we've reached the end
        if (CurrentAnimTime >= 1.0f)
        {
            CurrentAnimTime = FMath::Fmod(CurrentAnimTime, 1.0f);
        }
        
        // Update the mesh's animation time as well
        if (EffectAppendixMesh.IsValid())
        {
            EffectAppendixMesh->SetAnimationTime(CurrentAnimTime);
        }
        
        // Ensure the viewport is refreshed to show the updated animation
        // Only invalidate every few frames to reduce flickering
        static int32 FrameCount = 0;
        if (++FrameCount % 3 == 0) // Only refresh every 3 frames
        {
            Invalidate();
        }
    }
    
    // Make sure the mesh is still valid
    if (!EffectAppendixMesh.IsValid())
    {
        return;
    }
    
    // If we don't have a mesh component but we have a valid mesh, create one
    if (!MeshComponent.IsValid() && EffectAppendixMesh.IsValid())
    {
        // Get the preview mesh from the effect appendix mesh
        UStaticMeshComponent* PreviewComponent = EffectAppendixMesh->GetPreviewMesh();
        if (PreviewComponent && PreviewComponent->GetStaticMesh())
        {
            // Register it with the preview scene
            if (!PreviewComponent->IsRegistered())
            {
                PreviewScene->AddComponent(PreviewComponent, FTransform::Identity);
                MeshComponent = PreviewComponent;
            }
        }
    }
}

void FEffectAppendixMeshEditorViewportClient::Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI)
{
    FEditorViewportClient::Draw(View, PDI);
    
    // If we have a valid mesh, let's draw it with animation visualization
    if (EffectAppendixMesh.IsValid())
    {
        // Draw basic mesh wireframe
        DrawMeshWireframe(PDI);
        
        // Draw animated vertices based on timeline
        DrawAnimatedVertices(PDI);
    }
}

// Helper function to draw the basic mesh wireframe
void FEffectAppendixMeshEditorViewportClient::DrawMeshWireframe(FPrimitiveDrawInterface* PDI)
{
    if (!EffectAppendixMesh.IsValid() || !PDI)
        return;
        
    const TArray<FVector>& Vertices = EffectAppendixMesh->VertexPositions;
    const TArray<uint16>& Indices = EffectAppendixMesh->IndexBuffer;
    
    // Draw wireframe of the mesh
    FColor WireframeColor(100, 255, 150, 192);  // Semi-transparent green
    
    // Iterate through triangles and draw wireframe
    for (int32 i = 0; i < Indices.Num(); i += 3)
    {
        if (i + 2 < Indices.Num())
        {
            uint16 idx1 = Indices[i];
            uint16 idx2 = Indices[i+1];
            uint16 idx3 = Indices[i+2];
            
            // Validate indices
            if (idx1 < (uint16)Vertices.Num() && 
                idx2 < (uint16)Vertices.Num() && 
                idx3 < (uint16)Vertices.Num())
            {
                FVector v1 = Vertices[idx1];
                FVector v2 = Vertices[idx2];
                FVector v3 = Vertices[idx3];
                
                // Draw lines for each triangle edge
                PDI->DrawLine(v1, v2, WireframeColor, SDPG_Foreground);
                PDI->DrawLine(v2, v3, WireframeColor, SDPG_Foreground);
                PDI->DrawLine(v3, v1, WireframeColor, SDPG_Foreground);
            }
        }
    }
}

// Helper function to draw the animated vertices based on timeline
void FEffectAppendixMeshEditorViewportClient::DrawAnimatedVertices(FPrimitiveDrawInterface* PDI)
{
    if (!EffectAppendixMesh.IsValid() || !PDI)
        return;
        
    const TArray<FVector>& Vertices = EffectAppendixMesh->VertexPositions;
    const TArray<uint16>& Indices = EffectAppendixMesh->IndexBuffer;
    const TArray<uint16>& TimeMap = EffectAppendixMesh->TimeToTriangleMap;
    const TArray<float>& Timeline = EffectAppendixMesh->Timeline;
    
    if (TimeMap.Num() == 0 || Timeline.Num() == 0)
        return;
        
    // Calculate which triangles should be active based on current animation time
    int32 ActiveTriangleCount = FMath::FloorToInt(CurrentAnimTime * TimeMap.Num());
    
    // Color for active vertices
    FColor ActiveColor(255, 50, 50, 255);   // Bright red for latest active vertices
    FColor TrailColor(255, 255, 50, 255);   // Yellow for earlier active vertices
    
    // Draw active triangles
    for (int32 i = 0; i < ActiveTriangleCount && i < TimeMap.Num(); ++i)
    {
        uint16 TriangleIdx = TimeMap[i];
        int32 VertexIdx = TriangleIdx * 3;
        
        if (VertexIdx + 2 < Indices.Num())
        {
            uint16 idx1 = Indices[VertexIdx];
            uint16 idx2 = Indices[VertexIdx + 1];
            uint16 idx3 = Indices[VertexIdx + 2];
            
            if (idx1 < (uint16)Vertices.Num() && 
                idx2 < (uint16)Vertices.Num() && 
                idx3 < (uint16)Vertices.Num())
            {
                FVector v1 = Vertices[idx1];
                FVector v2 = Vertices[idx2];
                FVector v3 = Vertices[idx3];
                
                // Calculate interpolation factor for color fade (0 = oldest, 1 = newest)
                float ColorFactor = (float)i / FMath::Max(1.0f, (float)ActiveTriangleCount);
                
                // Manually interpolate between trail color and active color
                FColor VertexColor;
                VertexColor.R = FMath::Lerp((float)TrailColor.R, (float)ActiveColor.R, ColorFactor);
                VertexColor.G = FMath::Lerp((float)TrailColor.G, (float)ActiveColor.G, ColorFactor);
                VertexColor.B = FMath::Lerp((float)TrailColor.B, (float)ActiveColor.B, ColorFactor);
                VertexColor.A = 255;
                
                // Draw points at vertices with size based on importance (newer = bigger)
                float PointSize = FMath::Lerp(2.0f, 6.0f, ColorFactor);
                
                // Draw vertices
                PDI->DrawPoint(v1, VertexColor, PointSize, SDPG_Foreground);
                PDI->DrawPoint(v2, VertexColor, PointSize, SDPG_Foreground);
                PDI->DrawPoint(v3, VertexColor, PointSize, SDPG_Foreground);
                
                // Draw filled triangle for the most recent active triangle
                if (i == ActiveTriangleCount - 1)
                {
                    // Use engine debug material for drawing the triangle
                    DrawTriangle(PDI, v1, v2, v3, GEngine->DebugEditorMaterial->GetRenderProxy(), SDPG_Foreground);
                }
            }
        }
    }
}

void FEffectAppendixMeshEditorViewportClient::DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas)
{
    FEditorViewportClient::DrawCanvas(InViewport, View, Canvas);
    
    // Add time display to viewport
    if (EffectAppendixMesh.IsValid())
    {
        UFont* Font = GEngine->GetSmallFont();
        
        // Display info about the animation time
        FString TimeString = FString::Printf(TEXT("Animation Time: %.2f / %.2f seconds"), 
                                             CurrentAnimTime * TotalAnimationTime, 
                                             TotalAnimationTime);
        
        Canvas.DrawShadowedText(
            10.0f,
            10.0f,
            FText::FromString(TimeString),
            Font,
            FLinearColor::White
        );
        
        // Display playback info
        FString PlaybackString = FString::Printf(TEXT("%s - Speed: %.1fx"), 
                                                bIsPlaying ? TEXT("PLAYING") : TEXT("PAUSED"), 
                                                PlaybackSpeed);
        
        Canvas.DrawShadowedText(
            10.0f,
            30.0f,
            FText::FromString(PlaybackString),
            Font,
            bIsPlaying ? FLinearColor::Green : FLinearColor::Yellow
        );
    }
}

void FEffectAppendixMeshEditorViewportClient::StartAnimation()
{
    bIsPlaying = true;
}

void FEffectAppendixMeshEditorViewportClient::PauseAnimation()
{
    bIsPlaying = false;
}

void FEffectAppendixMeshEditorViewportClient::StopAnimation()
{
    bIsPlaying = false;
    CurrentAnimTime = 0.0f;
    Invalidate();
}

void FEffectAppendixMeshEditorViewportClient::SetPlaybackSpeed(float Speed)
{
    PlaybackSpeed = FMath::Max(0.1f, Speed);
}

void FEffectAppendixMeshEditorViewportClient::SetCurrentAnimationTime(float Time)
{
    CurrentAnimTime = FMath::Clamp(Time, 0.0f, 1.0f);
    Invalidate();
}

//////////////////////////////////////////////////////////////////////////
// SEffectAppendixMeshEditorViewport

void SEffectAppendixMeshEditorViewport::Construct(const FArguments& InArgs, TSharedPtr<FEffectAppendixMeshEditor> InEffectAppendixMeshEditor)
{
    EffectAppendixMeshEditorPtr = InEffectAppendixMeshEditor;
    
    SEditorViewport::Construct(SEditorViewport::FArguments());
}

SEffectAppendixMeshEditorViewport::~SEffectAppendixMeshEditorViewport()
{
    if (EditorViewportClient.IsValid())
    {
        EditorViewportClient->Viewport = nullptr;
    }
}

TSharedRef<FEditorViewportClient> SEffectAppendixMeshEditorViewport::MakeEditorViewportClient()
{
    // Initialize the viewport client
    EditorViewportClient = MakeShareable(new FEffectAppendixMeshEditorViewportClient(PreviewScene, SharedThis(this)));
    
    return EditorViewportClient.ToSharedRef();
}

void FEffectAppendixMeshEditorViewportClient::SetEffectAppendixMesh(UEffectAppendixMesh* InEffectAppendixMesh)
{
    // Clear any existing component first
    if (MeshComponent.IsValid())
    {
        PreviewScene->RemoveComponent(MeshComponent.Get());
        MeshComponent = nullptr;
    }
    
    EffectAppendixMesh = InEffectAppendixMesh;
    
    // If we have a new valid mesh, get its component and setup animation parameters
    if (EffectAppendixMesh.IsValid())
    {
        // Get the total animation time from the mesh
        TotalAnimationTime = EffectAppendixMesh->HalfToFloat(EffectAppendixMesh->TotalTime);
        if (TotalAnimationTime <= 0.0f)
        {
            TotalAnimationTime = 1.0f;  // Default to 1 second if not specified
        }
        
        UStaticMeshComponent* PreviewComponent = EffectAppendixMesh->GetPreviewMesh();
        if (PreviewComponent && PreviewComponent->GetStaticMesh())
        {
            // Register it with the preview scene
            PreviewScene->AddComponent(PreviewComponent, FTransform::Identity);
            MeshComponent = PreviewComponent;
        }
    }
    
    // Refresh the viewport
    Invalidate();
}

void SEffectAppendixMeshEditorViewport::OnPlayClicked()
{
    if (EditorViewportClient.IsValid())
    {
        EditorViewportClient->StartAnimation();
    }
}

void SEffectAppendixMeshEditorViewport::OnPauseClicked()
{
    if (EditorViewportClient.IsValid())
    {
        EditorViewportClient->PauseAnimation();
    }
}

void SEffectAppendixMeshEditorViewport::OnStopClicked()
{
    if (EditorViewportClient.IsValid())
    {
        EditorViewportClient->StopAnimation();
        
        // Reset the scrubber
        if (TimelineSlider.IsValid())
        {
            TimelineSlider->SetValue(0.0f);
        }
    }
}

void SEffectAppendixMeshEditorViewport::OnScrubValueChanged(float NewValue)
{
    // Get the asset
    TSharedPtr<FEffectAppendixMeshEditor> Editor = EffectAppendixMeshEditorPtr.Pin();
    UEffectAppendixMesh* EffectAppendixMesh = nullptr;
    if (Editor.IsValid())
    {
        EffectAppendixMesh = Editor->GetEffectAppendixMeshBeingEdited();
    }

    if (EditorViewportClient.IsValid())
    {
        // Update the viewport client's animation time
        EditorViewportClient->SetCurrentAnimationTime(NewValue);
        
        // Also update the mesh's animation time for consistency
        if (EffectAppendixMesh)
        {
            EffectAppendixMesh->SetAnimationTime(NewValue);
        }
        
        // Update time text with proper formatting
        if (TimeText.IsValid() && EffectAppendixMesh)
        {
            float TotalTime = EffectAppendixMesh->GetTotalAnimationTimeInSeconds();
            float CurrentTime = NewValue * TotalTime;
            FText TimeString = FText::Format(NSLOCTEXT("EffectAppendixMeshEditor", "TimeFormat", "{0:.2f} / {1:.2f} sec"),
                                          FText::AsNumber(CurrentTime),
                                          FText::AsNumber(TotalTime));
            TimeText->SetText(TimeString);
        }
    }
}

void SEffectAppendixMeshEditorViewport::UpdateAnimationTiming()
{
    // Get the asset
    TSharedPtr<FEffectAppendixMeshEditor> Editor = EffectAppendixMeshEditorPtr.Pin();
    UEffectAppendixMesh* EffectAppendixMesh = nullptr;
    if (Editor.IsValid())
    {
        EffectAppendixMesh = Editor->GetEffectAppendixMeshBeingEdited();
    }
    
    if (EditorViewportClient.IsValid() && EffectAppendixMesh)
    {
        // Update the time display
        float TotalTime = EffectAppendixMesh->GetTotalAnimationTimeInSeconds();
        float CurrentTime = EditorViewportClient->GetCurrentAnimationTime() * TotalTime;
        
        if (TimeText.IsValid())
        {
            FText TimeString = FText::Format(NSLOCTEXT("EffectAppendixMeshEditor", "TimeFormat", "{0:.2f} / {1:.2f} sec"),
                                          FText::AsNumber(CurrentTime),
                                          FText::AsNumber(TotalTime));
            TimeText->SetText(TimeString);
        }
    }
}

void SEffectAppendixMeshEditorViewport::SetEffectAppendixMesh(UEffectAppendixMesh* InEffectAppendixMesh)
{
    if (EditorViewportClient.IsValid())
    {
        EditorViewportClient->SetEffectAppendixMesh(InEffectAppendixMesh);
        
        // Reset the scrubber
        if (TimelineSlider.IsValid())
        {
            TimelineSlider->SetValue(0.0f);
        }
        
        // Update the timing display
        UpdateAnimationTiming();
    }
}

TSharedPtr<SWidget> SEffectAppendixMeshEditorViewport::MakeViewportToolbar()
{
    return SNew(SBorder)
        .BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
        .HAlign(HAlign_Center)
        [
            SNew(SHorizontalBox)
            
            // Play button
            +SHorizontalBox::Slot()
            .AutoWidth()
            .Padding(2.0f)
            [
                SNew(SButton)
                .ButtonStyle(FEditorStyle::Get(), "FlatButton.Success")
                .OnClicked_Lambda([this]() { 
                    OnPlayClicked(); 
                    return FReply::Handled();
                })
                .ToolTipText(NSLOCTEXT("EffectAppendixMeshEditor", "Play", "Play Animation"))
                .Content()
                [
                    SNew(STextBlock)
                    .Text(NSLOCTEXT("EffectAppendixMeshEditor", "PlayText", "Play"))
                ]
            ]
            
            // Pause button
            +SHorizontalBox::Slot()
            .AutoWidth()
            .Padding(2.0f)
            [
                SNew(SButton)
                .ButtonStyle(FEditorStyle::Get(), "FlatButton.Warning")
                .OnClicked_Lambda([this]() { 
                    OnPauseClicked(); 
                    return FReply::Handled();
                })
                .ToolTipText(NSLOCTEXT("EffectAppendixMeshEditor", "Pause", "Pause Animation"))
                .Content()
                [
                    SNew(STextBlock)
                    .Text(NSLOCTEXT("EffectAppendixMeshEditor", "PauseText", "Pause"))
                ]
            ]
            
            // Stop button
            +SHorizontalBox::Slot()
            .AutoWidth()
            .Padding(2.0f)
            [
                SNew(SButton)
                .ButtonStyle(FEditorStyle::Get(), "FlatButton.Danger")
                .OnClicked_Lambda([this]() { 
                    OnStopClicked(); 
                    return FReply::Handled();
                })
                .ToolTipText(NSLOCTEXT("EffectAppendixMeshEditor", "Stop", "Stop Animation"))
                .Content()
                [
                    SNew(STextBlock)
                    .Text(NSLOCTEXT("EffectAppendixMeshEditor", "StopText", "Stop"))
                ]
            ]
            
            // Timeline scrubber
            +SHorizontalBox::Slot()
            .FillWidth(1.0f)
            .Padding(8.0f, 0.0f)
            .VAlign(VAlign_Center)
            [
                SAssignNew(TimelineSlider, SSlider)
                .Value(0.0f)
                .OnValueChanged(this, &SEffectAppendixMeshEditorViewport::OnScrubValueChanged)
            ]
            
            // Time display
            +SHorizontalBox::Slot()
            .AutoWidth()
            .Padding(2.0f)
            .VAlign(VAlign_Center)
            [
                SAssignNew(TimeText, STextBlock)
                .Text(NSLOCTEXT("EffectAppendixMeshEditor", "InitialTimeText", "0.00 / 0.00 sec"))
                .MinDesiredWidth(80.0f)
            ]
        ];
}
