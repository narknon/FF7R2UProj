#include "RebirthPreviewCameraLibrary.h"
#include "Camera/CameraActor.h"
#include "Dom/JsonObject.h"
#include "Editor.h"
#include "Engine/World.h"
#include "LevelEditorViewport.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UnrealClient.h"
#include "Application/ThrottleManager.h"
#include "RenderingThread.h"
#include "SceneManagement.h"
#include "SceneView.h"

FString URebirthPreviewCameraLibrary::ConfigureOwnedPreviewCamera()
{
    const TSharedRef<FJsonObject> Report = MakeShared<FJsonObject>();
    Report->SetBoolField(TEXT("success"), false);
    auto Result = [&Report](const TCHAR* Reason)
    {
        Report->SetStringField(TEXT("reason"), Reason);
        FString Text;
        FJsonSerializer::Serialize(Report, TJsonWriterFactory<>::Create(&Text));
        return Text;
    };
    if (!IsInGameThread() || IsRunningCommandlet() || !GEditor ||
        !FParse::Param(FCommandLine::Get(), TEXT("RebirthCharacterPreview")))
    {
        return Result(TEXT("owned_rendering_preview_host_required"));
    }
    FViewport* Active = GEditor->GetActiveViewport();
    for (FLevelEditorViewportClient* Client : GEditor->GetLevelViewportClients())
    {
        if (!Client || !Active || Client->Viewport != Active || Active->GetClient() != Client) continue;
        ACameraActor* Camera = Cast<ACameraActor>(Client->GetActiveActorLock().Get());
        UWorld* World = Client->GetWorld();
        if (!World || World->IsGameWorld() || !IsValid(Camera) || Camera->GetWorld() != World)
        {
            return Result(TEXT("piloted_camera_in_editor_world_required"));
        }
        // Keep the same lens/exposure/realtime state for temporal accumulation
        // and the final draw, rather than changing those only for readback.
        Client->SetRealtime(true);
        Client->bLockedCameraView = true;
        Client->UpdateViewForLockedActor(0.0f);
        Client->Invalidate();
        Report->SetBoolField(TEXT("success"), true);
        Report->SetBoolField(TEXT("realtime"), Client->IsRealtime());
        Report->SetNumberField(TEXT("view_fov"), Client->ViewFOV);
        Report->SetStringField(TEXT("camera"), Camera->GetPathName());
        return Result(TEXT("owned_camera_prepared"));
    }
    return Result(TEXT("active_level_editor_viewport_missing"));
}

FString URebirthPreviewCameraLibrary::WarmOwnedPreviewViewportFrame(float DeltaSeconds)
{
    const TSharedRef<FJsonObject> Report = MakeShared<FJsonObject>();
    Report->SetBoolField(TEXT("success"), false);
    auto Result = [&Report](const TCHAR* Reason)
    {
        Report->SetStringField(TEXT("reason"), Reason);
        FString Text;
        FJsonSerializer::Serialize(Report, TJsonWriterFactory<>::Create(&Text));
        return Text;
    };
    if (!IsInGameThread() || IsRunningCommandlet() || !GEditor ||
        !FParse::Param(FCommandLine::Get(), TEXT("RebirthCharacterPreview")) ||
        !FMath::IsFinite(DeltaSeconds) || DeltaSeconds <= 0.0f || DeltaSeconds > 0.25f)
    {
        return Result(TEXT("owned_rendering_preview_host_and_bounded_delta_required"));
    }
    FViewport* Active = GEditor->GetActiveViewport();
    for (FLevelEditorViewportClient* Client : GEditor->GetLevelViewportClients())
    {
        if (!Client || !Active || Client->Viewport != Active || Active->GetClient() != Client) continue;
        ACameraActor* Camera = Cast<ACameraActor>(Client->GetActiveActorLock().Get());
        UWorld* World = Client->GetWorld();
        if (!World || !World->Scene || World->IsGameWorld() || !IsValid(Camera) || Camera->GetWorld() != World)
        {
            return Result(TEXT("piloted_camera_in_editor_world_required"));
        }
        if (!Client->IsRealtime() || !FSlateThrottleManager::Get().IsAllowingExpensiveTasks())
        {
            return Result(TEXT("realtime_unthrottled_viewport_required"));
        }
        // A hidden editor window does not necessarily tick this client. Tick
        // without re-piloting so its two-frame camera-cut latch can clear.
        Client->Tick(DeltaSeconds);
        FSceneViewFamilyContext Family(FSceneViewFamily::ConstructionValues(
            Active, Client->GetScene(), Client->EngineShowFlags).SetRealtimeUpdate(true));
        FSceneView* View = Client->CalcSceneView(&Family);
        if (!View || !View->State) return Result(TEXT("persistent_view_state_required"));
        Report->SetBoolField(TEXT("camera_cut"), View->bCameraCut);
        Report->SetNumberField(TEXT("anti_aliasing_method"), static_cast<int32>(View->AntiAliasingMethod));
        Report->SetNumberField(TEXT("sample_before"), View->State->GetCurrentTemporalAASampleIndex());
        World->SendAllEndOfFrameUpdates();
        Active->Draw(false);
        FlushRenderingCommands();
        Report->SetNumberField(TEXT("sample_after"), View->State->GetCurrentTemporalAASampleIndex());
        Report->SetBoolField(TEXT("success"), true);
        return Result(TEXT("owned_temporal_frame_rendered"));
    }
    return Result(TEXT("active_level_editor_viewport_missing"));
}
