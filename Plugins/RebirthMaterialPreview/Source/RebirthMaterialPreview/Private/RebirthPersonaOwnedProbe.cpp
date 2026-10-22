#include "RebirthPersonaOwnedProbe.h"

#include "CoreMinimal.h"

#include "Editor.h"

#include "Subsystems/AssetEditorSubsystem.h"

#include "IAnimationEditor.h"

#include "ISkeletonEditor.h"

#include "ISkeletalMeshEditor.h"

#include "IPersonaToolkit.h"

#include "IPersonaPreviewScene.h"

#include "PersonaModule.h"

#include "IPersonaViewport.h"

#include "EditorViewportClient.h"
#include "CameraController.h"
#include "Containers/Ticker.h"
#include "InputCoreTypes.h"
#include "Preferences/PersonaOptions.h"

#include "UnrealClient.h"

#include "RenderingThread.h"
#include "SceneView.h"
#include "SceneManagement.h"
#include "SceneViewExtension.h"

#include "ImageUtils.h"

#include "Misc/App.h"

#include "AssetToolsModule.h"

#include "IAssetTools.h"

#include "IAssetTypeActions.h"

#include "ToolMenu.h"

#include "ToolMenuSection.h"

#include "Framework/Commands/InputBindingManager.h"

#include "Framework/Commands/UICommandList.h"

#include "Framework/Commands/UICommandInfo.h"

#include "Materials/MaterialInterface.h"

#include "Widgets/Docking/SDockTab.h"

#include "Animation/DebugSkelMeshComponent.h"

#include "AnimPreviewInstance.h"

#include "Animation/AnimSequence.h"

#include "Animation/Skeleton.h"

#include "Engine/SkeletalMesh.h"

#include "Engine/World.h"

#include "Framework/Docking/TabManager.h"

#include "HAL/IConsoleManager.h"

#include "HAL/FileManager.h"

#include "Misc/CommandLine.h"

#include "Misc/FileHelper.h"

#include "Misc/Paths.h"

#include "Misc/Parse.h"

#include "Misc/SecureHash.h"

#include "Serialization/JsonSerializer.h"

#include "Dom/JsonObject.h"

#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthPersonaOwnedProbe, Log, All);

namespace RebirthPersonaOwnedProbe

{

namespace

{

struct FObservedScene : TSharedFromThis<FObservedScene>

{

    TWeakPtr<IPersonaPreviewScene> Scene;

    int32 PostTicks = 0;

    void AfterTick() { ++PostTicks; }

};

TArray<TSharedPtr<FObservedScene>> Scenes;

TArray<TWeakObjectPtr<UObject>> OwnedAssets;

TWeakObjectPtr<UObject> ActiveAsset;

FDelegateHandle SceneCreatedHandle;

TUniquePtr<FAutoConsoleCommand> Command;

uint64 ReportSerial = 0;

TSharedPtr<FJsonObject> LastMenu;

TSharedPtr<FJsonObject> LastCapture;

TSharedPtr<FJsonObject> LastCommands;

// Owned-process diagnostics only. Count native renderer submissions for exactly
// this Persona viewport; never modify a view family, view, material or cvar.
class FOwnedPersonaViewObserver final : public FSceneViewExtensionBase
{
public:
    explicit FOwnedPersonaViewObserver(const FAutoRegister& AutoRegister) : FSceneViewExtensionBase(AutoRegister) {}
    FViewport* ExpectedViewport = nullptr;
    uint64 DistinctDrawFrames = 0;
    uint64 LastEngineFrame = MAX_uint64;
    int32 FinalAAMethod = INDEX_NONE;
    bool bRealtime = false, bTemporalAA = false, bAntiAliasing = false, bPostProcessing = false;
    uint32 StartOcclusionFrame = 0;
    void Begin(FViewport* Viewport, uint32 OcclusionFrame)
    {
        check(IsInGameThread());
        ExpectedViewport = Viewport; DistinctDrawFrames = 0; LastEngineFrame = MAX_uint64;
        FinalAAMethod = INDEX_NONE; StartOcclusionFrame = OcclusionFrame;
    }
    virtual bool IsActiveThisFrame(FViewport* Viewport) const override
    { return IsInGameThread() && ExpectedViewport && Viewport == ExpectedViewport; }
    virtual void SetupViewFamily(FSceneViewFamily&) override {}
    virtual void SetupView(FSceneViewFamily&, FSceneView&) override {}
    virtual void BeginRenderViewFamily(FSceneViewFamily& Family) override
    {
        if (!IsInGameThread() || Family.RenderTarget != ExpectedViewport || Family.EngineShowFlags.HitProxies || Family.Views.Num() != 1) { return; }
        if (LastEngineFrame != GFrameCounter) { ++DistinctDrawFrames; LastEngineFrame = GFrameCounter; }
        FinalAAMethod = static_cast<int32>(Family.Views[0]->AntiAliasingMethod);
        bRealtime = Family.bRealtimeUpdate; bTemporalAA = Family.EngineShowFlags.TemporalAA;
        bAntiAliasing = Family.EngineShowFlags.AntiAliasing; bPostProcessing = Family.EngineShowFlags.PostProcessing;
    }
    virtual void PreRenderViewFamily_RenderThread(FRHICommandListImmediate&, FSceneViewFamily&) override {}
    virtual void PreRenderView_RenderThread(FRHICommandListImmediate&, FSceneView&) override {}
};
TSharedPtr<FOwnedPersonaViewObserver, ESPMode::ThreadSafe> ViewObserver;
TSharedPtr<FJsonObject> LastFraming;

// Only the explicitly owned, already opened native Persona viewport is held.
// A weak widget owns no client lifetime; the raw pointer below is identity only.
struct FOwnedCameraClamp
{
    TWeakPtr<IPersonaViewport> Widget;
    FEditorViewportClient* ClientIdentity = nullptr; // Comparison only; pin Widget before access.
    FEditorCameraController* ControllerIdentity = nullptr;
    bool bOriginalDisableInput = false;
    FCameraControllerConfig OriginalConfig;
    double ExpiresAt = 0.0;
};
TUniquePtr<FOwnedCameraClamp> CameraClamp;
FDelegateHandle CameraClampExpiryHandle;
bool bLastCameraRestoreSucceeded = true;
FString LastCameraRestoreReason = TEXT("not_started");
bool bLastOriginalDisableInput = false;
bool bLastInputRestoreSucceeded = true;
bool bLastRestoredDisableInput = false;
bool bInputRestoreObserved = false;

bool RestoreOwnedCameraClamp(const TCHAR* Reason, bool bRemoveExpiryTicker = true)
{
    check(IsInGameThread());
    if (bRemoveExpiryTicker && CameraClampExpiryHandle.IsValid())
    { FTicker::GetCoreTicker().RemoveTicker(CameraClampExpiryHandle); CameraClampExpiryHandle.Reset(); }
    if (!CameraClamp.IsValid()) { return true; }
    TSharedPtr<IPersonaViewport> Widget = CameraClamp->Widget.Pin();
    if (!Widget.IsValid())
    {
        // The widget/client/controller no longer exist. Never follow an old pointer.
        CameraClamp.Reset(); bLastCameraRestoreSucceeded = true;
        LastCameraRestoreReason = FString(Reason) + TEXT(":viewport_destroyed"); return true;
    }
    FEditorViewportClient& Client = Widget->GetViewportClient();
    if (&Client != CameraClamp->ClientIdentity)
    {
        // A replacement client never receives saved state from its predecessor.
        CameraClamp.Reset(); bLastCameraRestoreSucceeded = false; bLastInputRestoreSucceeded = false;
        LastCameraRestoreReason = FString(Reason) + TEXT(":client_identity_changed_restore_refused"); return false;
    }
    // Input belongs to the live client, independently of controller lifetime.
    // Restore it before refusing a replaced controller; never leave input held.
    Client.bDisableInput = CameraClamp->bOriginalDisableInput;
    bLastRestoredDisableInput = Client.bDisableInput; bInputRestoreObserved = true;
    bLastInputRestoreSucceeded = Client.bDisableInput == CameraClamp->bOriginalDisableInput;
    FEditorCameraController* Controller = Client.GetCameraController();
    if (!Controller || Controller != CameraClamp->ControllerIdentity)
    {
        bLastCameraRestoreSucceeded = false;
        LastCameraRestoreReason = FString(Reason) + TEXT(":controller_identity_changed_restore_refused");
        UE_LOG(LogRebirthPersonaOwnedProbe, Error, TEXT("Owned camera restore refused: live controller identity changed."));
        CameraClamp.Reset(); // Input is already restored; discard stale controller identity.
        return false; // Never write the saved config into a different controller.
    }
    Controller->SetConfig(CameraClamp->OriginalConfig); // Entire exact original value.
    CameraClamp.Reset(); bLastCameraRestoreSucceeded = true;
    LastCameraRestoreReason = Reason; return true;
}

bool BeginOwnedCameraClamp(const TSharedPtr<IPersonaViewport>& Widget)
{
    if (!RestoreOwnedCameraClamp(TEXT("reframe")) || !Widget.IsValid()) { return false; }
    FEditorViewportClient& Client = Widget->GetViewportClient();
    FEditorCameraController* Controller = Client.GetCameraController();
    if (!Controller) { return false; }
    CameraClamp = MakeUnique<FOwnedCameraClamp>();
    CameraClamp->Widget = Widget; CameraClamp->ClientIdentity = &Client; CameraClamp->ControllerIdentity = Controller;
    CameraClamp->bOriginalDisableInput = Client.bDisableInput;
    bLastOriginalDisableInput = Client.bDisableInput;
    Client.bDisableInput = true; // Owned bounded capture only; native Slate/Tick/Draw continue.
    CameraClamp->OriginalConfig = Controller->GetConfig();
    CameraClamp->ExpiresAt = FPlatformTime::Seconds() + 125.0;
    FCameraControllerConfig Held = CameraClamp->OriginalConfig;
    Held.MaximumMovementSpeed = 0.0f; Held.MaximumRotationSpeed = 0.0f;
    Held.MaximumFOVSpeed = 0.0f; Held.bEnableFOVRecoil = false;
    Controller->SetConfig(Held);
    CameraClampExpiryHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([](float)
    {
        if (!CameraClamp.IsValid()) { CameraClampExpiryHandle.Reset(); return false; }
        if (FPlatformTime::Seconds() < CameraClamp->ExpiresAt) { return true; }
        CameraClampExpiryHandle.Reset(); RestoreOwnedCameraClamp(TEXT("125_second_expiry"), false);
        return false;
    }));
    return true;
}


TArray<TSharedPtr<FJsonValue>> VectorJSON(const FVector& V)
{
    return { MakeShared<FJsonValueNumber>(V.X), MakeShared<FJsonValueNumber>(V.Y), MakeShared<FJsonValueNumber>(V.Z) };
}

TSharedRef<FJsonObject> ViewportTelemetry(FEditorViewportClient& Client)
{
    TSharedRef<FJsonObject> State = MakeShared<FJsonObject>();
    State->SetArrayField(TEXT("camera_location"), VectorJSON(Client.GetViewLocation()));
    State->SetArrayField(TEXT("camera_rotation_pyr"), VectorJSON(FVector(Client.GetViewRotation().Pitch, Client.GetViewRotation().Yaw, Client.GetViewRotation().Roll)));
    State->SetNumberField(TEXT("view_fov_degrees"), Client.ViewFOV);
    State->SetBoolField(TEXT("client_realtime"), Client.IsRealtime());
    State->SetBoolField(TEXT("native_focus_transition_playing"), Client.GetViewTransform().IsPlaying());
    State->SetArrayField(TEXT("native_orbit_look_at"), VectorJSON(Client.GetViewTransform().GetLookAt()));
    State->SetBoolField(TEXT("native_should_orbit_camera"), Client.ShouldOrbitCamera());
    State->SetBoolField(TEXT("native_camera_locked"), Client.IsCameraLocked());
    State->SetBoolField(TEXT("native_flight_camera_active"), Client.IsFlightCameraActive());
    TSharedPtr<IPersonaViewport> HeldWidget = CameraClamp.IsValid() ? CameraClamp->Widget.Pin() : nullptr;
    const bool bHeldClient = HeldWidget.IsValid() && &HeldWidget->GetViewportClient() == &Client && CameraClamp->ClientIdentity == &Client;
    State->SetBoolField(TEXT("native_viewport_input_disabled"), Client.bDisableInput);
    State->SetBoolField(TEXT("owned_camera_input_held"), bHeldClient && Client.bDisableInput);
    State->SetBoolField(TEXT("owned_camera_original_input_disabled"), bHeldClient ? CameraClamp->bOriginalDisableInput : bLastOriginalDisableInput);
    State->SetBoolField(TEXT("owned_camera_input_last_restore_succeeded"), bLastInputRestoreSucceeded);
    State->SetBoolField(TEXT("owned_camera_input_last_restored_disabled"), bLastRestoredDisableInput);
    State->SetBoolField(TEXT("owned_camera_input_restore_observed"), bInputRestoreObserved);
    State->SetBoolField(TEXT("owned_camera_controller_clamped"), bHeldClient && Client.GetCameraController() == CameraClamp->ControllerIdentity);
    State->SetBoolField(TEXT("owned_camera_last_restore_succeeded"), bLastCameraRestoreSucceeded);
    State->SetStringField(TEXT("owned_camera_last_restore_reason"), LastCameraRestoreReason);
    if (FEditorCameraController* Controller = Client.GetCameraController())
    {
        State->SetNumberField(TEXT("native_camera_max_movement_speed"), Controller->GetConfig().MaximumMovementSpeed);
        State->SetNumberField(TEXT("native_camera_max_rotation_speed"), Controller->GetConfig().MaximumRotationSpeed);
        State->SetNumberField(TEXT("native_camera_max_fov_speed"), Controller->GetConfig().MaximumFOVSpeed);
    }
    if (Client.Viewport)
    {
        TSharedRef<FJsonObject> Keys = MakeShared<FJsonObject>();
        for (const FKey& Key : { EKeys::W, EKeys::A, EKeys::S, EKeys::D, EKeys::Up, EKeys::Down, EKeys::Left, EKeys::Right, EKeys::LeftMouseButton, EKeys::RightMouseButton, EKeys::MiddleMouseButton, EKeys::LeftAlt, EKeys::RightAlt })
        { Keys->SetBoolField(Key.GetFName().ToString(), Client.Viewport->KeyState(Key)); }
        State->SetObjectField(TEXT("native_viewport_key_state"), Keys);
    }

    State->SetBoolField(TEXT("show_temporal_aa"), Client.EngineShowFlags.TemporalAA);
    State->SetBoolField(TEXT("show_anti_aliasing"), Client.EngineShowFlags.AntiAliasing);
    State->SetBoolField(TEXT("show_post_processing"), Client.EngineShowFlags.PostProcessing);
    for (const TCHAR* Name : { TEXT("r.DefaultFeature.AntiAliasing"), TEXT("r.PostProcessAAQuality"), TEXT("r.TemporalAASamples"), TEXT("r.ScreenPercentage") })
    {
        if (IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(Name)) { State->SetNumberField(Name, CVar->GetFloat()); }
    }
    if (ViewObserver.IsValid() && ViewObserver->ExpectedViewport == Client.Viewport)
    {
        // SceneVisibility.cpp increments this counter once per render. Flush
        // makes its read a completed-frame observation, not a synthetic tick.
        FlushRenderingCommands();
        FSceneViewStateInterface* ViewState = Client.ViewState.GetReference();
        const uint32 Completed = ViewState ? ViewState->GetOcclusionFrameCounter() : 0;
        State->SetNumberField(TEXT("completed_view_render_counter"), Completed);
        State->SetNumberField(TEXT("completed_view_renders_since_framing"), uint32(Completed - ViewObserver->StartOcclusionFrame));
        State->SetNumberField(TEXT("native_distinct_draw_frames_since_framing"), static_cast<double>(ViewObserver->DistinctDrawFrames));
        State->SetNumberField(TEXT("last_native_draw_engine_frame"), static_cast<double>(ViewObserver->LastEngineFrame));
        State->SetNumberField(TEXT("actual_final_aa_method"), ViewObserver->FinalAAMethod);
        State->SetBoolField(TEXT("actual_family_realtime"), ViewObserver->bRealtime);
        State->SetBoolField(TEXT("actual_show_temporal_aa"), ViewObserver->bTemporalAA);
        State->SetBoolField(TEXT("actual_show_anti_aliasing"), ViewObserver->bAntiAliasing);
        State->SetBoolField(TEXT("actual_show_post_processing"), ViewObserver->bPostProcessing);
        State->SetBoolField(TEXT("native_view_state_valid"), ViewState != nullptr);
        if (ViewState) { State->SetNumberField(TEXT("native_temporal_sample_index"), ViewState->GetCurrentUnclampedTemporalAASampleIndex()); }
    }
    if (LastFraming.IsValid()) { State->SetObjectField(TEXT("framing"), LastFraming); }
    return State;
}


bool IsOwnedProcess()

{

    return GEditor && !IsRunningCommandlet() && IsInGameThread()

        && FParse::Param(FCommandLine::Get(), TEXT("RebirthPersonaOwnedProbe"));

}

void ObserveScene(const TSharedRef<IPersonaPreviewScene>& Scene)

{

    TSharedPtr<FObservedScene> Observed = MakeShared<FObservedScene>();

    Observed->Scene = Scene;

    Scene->RegisterOnPostTick(FSimpleDelegate::CreateSP(Observed.ToSharedRef(), &FObservedScene::AfterTick));

    Scenes.Add(Observed);

}

bool Owns(UObject* Asset)

{

    for (const TWeakObjectPtr<UObject>& Owned : OwnedAssets)

    {

        if (Owned.Get() == Asset) { return true; }

    }

    return false;

}

FString ExpectedEditor(UObject* Asset)

{

    if (Cast<UAnimSequence>(Asset)) { return TEXT("AnimationEditor"); }

    if (Cast<USkeleton>(Asset)) { return TEXT("SkeletonEditor"); }

    if (Cast<USkeletalMesh>(Asset)) { return TEXT("SkeletalMeshEditor"); }

    return FString();

}

TSharedPtr<IPersonaToolkit> GetPersona(IAssetEditorInstance* Instance, FAssetEditorToolkit*& OutEditor)

{

    OutEditor = nullptr;

    if (!Instance) { return nullptr; }

    const FName Name = Instance->GetEditorName();

    if (Name == FName(TEXT("AnimationEditor")))

    {

        IAnimationEditor* Editor = static_cast<IAnimationEditor*>(Instance);

        OutEditor = Editor;

        return Editor->GetPersonaToolkit();

    }

    if (Name == FName(TEXT("SkeletonEditor")))

    {

        ISkeletonEditor* Editor = static_cast<ISkeletonEditor*>(Instance);

        OutEditor = Editor;

        return Editor->GetPersonaToolkit();

    }

    if (Name == FName(TEXT("SkeletalMeshEditor")))

    {

        ISkeletalMeshEditor* Editor = static_cast<ISkeletalMeshEditor*>(Instance);

        OutEditor = Editor;

        return Editor->GetPersonaToolkit();

    }

    return nullptr;

}

FString PoseDigest(const TArray<FTransform>& Pose, bool& bFinite)

{

    FMD5 Digest;

    bFinite = true;

    for (const FTransform& Transform : Pose)

    {

        const FVector T = Transform.GetTranslation();

        const FVector S = Transform.GetScale3D();

        const FQuat Q = Transform.GetRotation();

        const float Values[] = {T.X,T.Y,T.Z,Q.X,Q.Y,Q.Z,Q.W,S.X,S.Y,S.Z};

        for (float Value : Values) { bFinite &= FMath::IsFinite(Value); }

        bFinite &= Q.IsNormalized();

        Digest.Update(reinterpret_cast<const uint8*>(Values), sizeof(Values));

    }

    uint8 Bytes[16]; Digest.Final(Bytes);

    return BytesToHex(Bytes, UE_ARRAY_COUNT(Bytes)).ToLower();

}

TSharedPtr<IPersonaViewport> FindPersonaViewport(const TSharedRef<SWidget>& Widget, int32 Depth, int32& Budget)

{

    if (Depth > 32 || --Budget < 0) { return nullptr; }

    // Exact native Slate type provenance: Persona TabSpawners.cpp265 constructs

    // this class; SAnimationEditorViewport.h166 derives it from IPersonaViewport.

    if (Widget->GetType() == FName(TEXT("SAnimationEditorViewportTabBody")))

    { return StaticCastSharedRef<IPersonaViewport>(Widget); }

    FChildren* Children = Widget->GetChildren();

    if (Children)

    {

        for (int32 Index = 0; Index < Children->Num() && Budget > 0; ++Index)

        {

            TSharedPtr<IPersonaViewport> Found = FindPersonaViewport(Children->GetChildAt(Index), Depth + 1, Budget);

            if (Found.IsValid()) { return Found; }

        }

    }

    return nullptr;

}

bool InspectMenu(UObject* Object)

{

    LastMenu = MakeShared<FJsonObject>();

    TSharedPtr<IAssetTypeActions> Actions = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools")).Get().GetAssetTypeActionsForClass(Object->GetClass()).Pin();

    LastMenu->SetBoolField(TEXT("actions_valid"), Actions.IsValid());

    if (!Actions.IsValid()) { return false; }

    TArray<UObject*> Objects = {Object};

    LastMenu->SetBoolField(TEXT("has_actions"), Actions->HasActions(Objects));

    LastMenu->SetStringField(TEXT("action_display_name"), Actions->GetName().ToString());

    UToolMenu* Menu = NewObject<UToolMenu>(GetTransientPackage(), NAME_None, RF_Transient);

    Menu->InitMenu(FToolMenuOwner(), FName(TEXT("RebirthOwnedPersonaMenu")));

    FToolMenuSection& Section = Menu->AddSection(FName(TEXT("OwnedNativeAssetActions")));

    Actions->GetActions(Objects, Section);

    TArray<TSharedPtr<FJsonValue>> Entries;

    for (const FToolMenuSection& MenuSection : Menu->Sections)

    {

        for (const FToolMenuEntry& Entry : MenuSection.Blocks)

        {

            TSharedRef<FJsonObject> Row = MakeShared<FJsonObject>();

            Row->SetStringField(TEXT("section"), MenuSection.Name.ToString());

            Row->SetStringField(TEXT("name"), Entry.Name.ToString());

            Row->SetStringField(TEXT("label"), Entry.Label.Get(FText::GetEmpty()).ToString());

            Entries.Add(MakeShared<FJsonValueObject>(Row));

        }

    }

    LastMenu->SetArrayField(TEXT("entries"), Entries);

    LastMenu->SetNumberField(TEXT("entry_count"), Entries.Num());

    LastMenu->SetStringField(TEXT("scope"), TEXT("Actual registered AssetTools action, FToolMenuSection overload. Entries inspected; no command or submenu executed."));

    return Entries.Num() > 0;

}

bool FramePersona(FAssetEditorToolkit* Editor, IPersonaToolkit& Toolkit, const FString& Profile)
{
    if (Profile != TEXT("front") && Profile != TEXT("threequarter")) { return false; }
    TSharedPtr<FTabManager> Manager = Editor->GetTabManager();
    TSharedPtr<SDockTab> Tab = Manager.IsValid() ? Manager->FindExistingLiveTab(FTabId(FName(TEXT("Viewport")))) : nullptr;
    if (!Tab.IsValid()) { return false; }
    int32 Budget = 4096;
    TSharedPtr<IPersonaViewport> Widget = FindPersonaViewport(Tab->GetContent(), 0, Budget);
    UDebugSkelMeshComponent* Component = Toolkit.GetPreviewMeshComponent();
    if (!Widget.IsValid() || !IsValid(Component) || !IsValid(Component->SkeletalMesh)) { return false; }
    FEditorViewportClient& Client = Widget->GetViewportClient();
    if (!Client.Viewport || Client.Viewport->GetClient() != &Client || Client.GetWorld() != Component->GetWorld() || !ViewObserver.IsValid()) { return false; }
    const FIntPoint Size = Client.Viewport->GetSizeXY();
    if (Size.X < 64 || Size.Y < 64 || Size.X > 8192 || Size.Y > 8192) { return false; }
    // Union original geometry bounds (including transformed wings) and live
    // component/bone bounds. No skeleton/pose/component transform is changed.
    FBox Bounds = Component->SkeletalMesh->GetBounds().GetBox().TransformBy(Component->GetComponentTransform());
    Bounds += Component->Bounds.GetBox();
    const TArray<FTransform>& Pose = Component->GetComponentSpaceTransforms();
    if (Pose.Num() <= 0 || Pose.Num() > 16384) { return false; }
    for (const FTransform& Bone : Pose)
    {
        const FVector P = Component->GetComponentTransform().TransformPosition(Bone.GetTranslation());
        if (P.ContainsNaN()) { return false; }
        Bounds += P;
    }
    if (!Bounds.IsValid || Bounds.Min.ContainsNaN() || Bounds.Max.ContainsNaN() || Bounds.GetExtent().GetMax() <= 0.0f || Bounds.GetExtent().GetMax() > 100000.0f) { return false; }
    Bounds = Bounds.ExpandBy(FMath::Max(8.0f, Bounds.GetExtent().GetMax() * 0.04f));
    const FVector Target = Bounds.GetCenter();
    const FVector Backward = (Profile == TEXT("front") ? FVector(1.0f, 0.0f, 0.04f) : FVector(235.0f, -135.0f, 10.0f)).GetSafeNormal();
    const FRotator Rotation = (-Backward).Rotation();
    Client.SetViewRotation(Rotation);
    // Native CalcSceneView supplies the actual projection/aspect-axis policy.
    // It is a read-only projection calculation, not a render or synthetic tick.
    FSceneViewFamilyContext Family(FSceneViewFamily::ConstructionValues(Client.Viewport, Client.GetScene(), Client.EngineShowFlags).SetRealtimeUpdate(Client.IsRealtime()));
    FSceneView* View = Client.CalcSceneView(&Family);
    if (!View) { return false; }
    const FMatrix& Projection = View->ViewMatrices.GetProjectionMatrix();
    const float TanH = 1.0f / Projection.M[0][0], TanV = 1.0f / Projection.M[1][1];
    if (!FMath::IsFinite(TanH) || !FMath::IsFinite(TanV) || TanH <= 0.001f || TanV <= 0.001f) { return false; }
    float Distance = 100.0f;
    for (int32 Corner = 0; Corner < 8; ++Corner)
    {
        const FVector P((Corner & 1) ? Bounds.Max.X : Bounds.Min.X, (Corner & 2) ? Bounds.Max.Y : Bounds.Min.Y, (Corner & 4) ? Bounds.Max.Z : Bounds.Min.Z);
        const FVector InCamera = Rotation.UnrotateVector(P - Target);
        Distance = FMath::Max(Distance, FMath::Max(FMath::Abs(InCamera.Y) / TanH - InCamera.X, FMath::Abs(InCamera.Z) / TanV - InCamera.X));
        Distance = FMath::Max(Distance, 20.0f - InCamera.X);
    }
    Distance *= 1.08f;
    if (!FMath::IsFinite(Distance) || Distance > 200000.0f) { return false; }
    if (!BeginOwnedCameraClamp(Widget)) { return false; }
    Client.SetLookAtLocation(Target, false);
    // SetViewLocation alone does not stop a still-playing native focus curve.
    Client.GetViewTransform().TransitionToLocation(Target + Backward * Distance, TWeakPtr<SWidget>(), true);
    Client.RequestRealTimeFrames(1024);
    Client.Invalidate();
    FlushRenderingCommands();
    FSceneViewStateInterface* State = Client.ViewState.GetReference();
    if (!State) { RestoreOwnedCameraClamp(TEXT("framing_view_state_missing")); return false; }
    ViewObserver->Begin(Client.Viewport, State->GetOcclusionFrameCounter());
    LastFraming = MakeShared<FJsonObject>();
    LastFraming->SetStringField(TEXT("profile"), Profile);
    LastFraming->SetArrayField(TEXT("world_bounds_min"), VectorJSON(Bounds.Min));
    LastFraming->SetArrayField(TEXT("world_bounds_max"), VectorJSON(Bounds.Max));
    LastFraming->SetNumberField(TEXT("distance_cm"), Distance);
    LastFraming->SetNumberField(TEXT("width"), Size.X); LastFraming->SetNumberField(TEXT("height"), Size.Y);
    LastFraming->SetNumberField(TEXT("tan_half_horizontal_fov"), TanH); LastFraming->SetNumberField(TEXT("tan_half_vertical_fov"), TanV);
    LastFraming->SetBoolField(TEXT("actual_geometry_component_bones_fitted"), true);
    LastFraming->SetBoolField(TEXT("asset_or_pose_modified"), false);
    LastFraming->SetBoolField(TEXT("owned_camera_hold_bounded_125_seconds"), true);
    // Public config observation only. The live Persona follow getter is private.
    LastFraming->SetStringField(TEXT("follow_mode_scope"), TEXT("Configured per-editor modes only; live private follow state is not inferred."));
    if (const UPersonaOptions* Options = GetDefault<UPersonaOptions>())
    {
        for (const FAssetEditorOptions& Option : Options->AssetEditorOptions)
        {
            if (Option.Context == Editor->GetToolkitFName())
            {
                TArray<TSharedPtr<FJsonValue>> FollowModes;
                for (const FViewportConfigOptions& ViewportConfig : Option.ViewportConfigs)
                { FollowModes.Add(MakeShared<FJsonValueNumber>(static_cast<uint8>(ViewportConfig.CameraFollowMode))); }
                LastFraming->SetArrayField(TEXT("configured_camera_follow_modes"), FollowModes); break;
            }
        }
    }

    return true;
}

bool CapturePersona(FAssetEditorToolkit* Editor, IPersonaToolkit& Toolkit, const FString& Label)

{

    LastCapture = MakeShared<FJsonObject>();

    LastCapture->SetBoolField(TEXT("success"), false);

    auto Fail = [](const FString& Reason) { LastCapture->SetStringField(TEXT("reason"), Reason); return false; };

    if (Label.IsEmpty() || Label.Len() > 64) { return Fail(TEXT("invalid_label")); }

    for (TCHAR Character : Label)

    {

        if (!FChar::IsAlnum(Character) && Character != TCHAR('_') && Character != TCHAR('-')) { return Fail(TEXT("invalid_label")); }

    }

    if (!FApp::CanEverRender()) { return Fail(TEXT("rendering_unavailable")); }

    static bool bCapturing = false;

    if (bCapturing) { return Fail(TEXT("recursive_capture_refused")); }

    TGuardValue<bool> CaptureGuard(bCapturing, true);

    TSharedPtr<FTabManager> Manager = Editor->GetTabManager();

    TSharedPtr<SDockTab> Tab = Manager.IsValid() ? Manager->FindExistingLiveTab(FTabId(FName(TEXT("Viewport")))) : nullptr;

    if (!Tab.IsValid()) { return Fail(TEXT("native_viewport_tab_missing")); }

    int32 Budget = 4096;

    TSharedPtr<IPersonaViewport> Widget = FindPersonaViewport(Tab->GetContent(), 0, Budget);

    LastCapture->SetNumberField(TEXT("widget_search_remaining_budget"), Budget);

    if (!Widget.IsValid()) { return Fail(TEXT("exact_native_persona_viewport_widget_missing")); }

    FEditorViewportClient& Client = Widget->GetViewportClient();

    FViewport* Viewport = Client.Viewport;

    UDebugSkelMeshComponent* Component = Toolkit.GetPreviewMeshComponent();

    UWorld* World = IsValid(Component) ? Component->GetWorld() : nullptr;

    if (!Viewport || Viewport->GetClient() != &Client || !World || Client.GetWorld() != World)

    { return Fail(TEXT("native_viewport_scene_identity_mismatch")); }

    const FIntPoint Size = Viewport->GetSizeXY();

    const int64 Count = int64(Size.X) * int64(Size.Y);

    LastCapture->SetNumberField(TEXT("width"), Size.X); LastCapture->SetNumberField(TEXT("height"), Size.Y);

    if (Size.X < 64 || Size.Y < 64 || Size.X > 8192 || Size.Y > 8192 || Count > 16777216)

    { return Fail(TEXT("native_viewport_dimensions_not_ready_or_excessive")); }

    const FString Directory = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("PersonaOwnedProbe"));

    const FString Filename = FPaths::Combine(Directory, Label + TEXT(".png"));

    if (IFileManager::Get().FileExists(*Filename)) { return Fail(TEXT("capture_file_exists_preserve_evidence")); }

    IFileManager::Get().MakeDirectory(*Directory, true);

    // Read a genuinely rendered native viewport frame; do not manufacture a draw.
    FlushRenderingCommands();
    LastCapture->SetObjectField(TEXT("viewport_render"), ViewportTelemetry(Client));

    TArray<FColor> Pixels;

    const bool bRead = Viewport->GetSizeXY() == Size && Viewport->ReadPixels(Pixels, FReadSurfaceDataFlags(RCM_UNorm), FIntRect(0, 0, Size.X, Size.Y));

    LastCapture->SetBoolField(TEXT("read_succeeded"), bRead);

    LastCapture->SetNumberField(TEXT("pixel_count"), Pixels.Num());

    if (!bRead || int64(Pixels.Num()) != Count) { return Fail(TEXT("native_viewport_pixel_read_failed")); }

    for (FColor& Pixel : Pixels) { Pixel.A = 255; }

    TArray<uint8> PNG; FImageUtils::CompressImageArray(Size.X, Size.Y, Pixels, PNG);

    const uint8 Signature[] = {137, 80, 78, 71, 13, 10, 26, 10};

    if (PNG.Num() <= 8 || FMemory::Memcmp(PNG.GetData(), Signature, 8) != 0 || !FFileHelper::SaveArrayToFile(PNG, *Filename))

    { return Fail(TEXT("native_viewport_png_write_failed")); }

    LastCapture->SetStringField(TEXT("path"), FPaths::ConvertRelativePathToFull(Filename));

    LastCapture->SetNumberField(TEXT("png_bytes"), PNG.Num());

    LastCapture->SetBoolField(TEXT("captured_native_persona_viewport"), true);

    LastCapture->SetBoolField(TEXT("success"), true);

    return true;

}

bool InspectNativeCommandBindings(FAssetEditorToolkit* Editor)

{

    LastCommands = MakeShared<FJsonObject>();

    const FName Context = Editor->GetToolkitFName();

    TArray<TSharedPtr<FUICommandInfo>> Infos;

    FInputBindingManager::Get().GetCommandInfosFromContext(Context, Infos);

    LastCommands->SetStringField(TEXT("binding_context"), Context.ToString());

    LastCommands->SetNumberField(TEXT("registered_command_count"), Infos.Num());

    LastCommands->SetBoolField(TEXT("command_count_bounded"), Infos.Num() <= 256);

    TArray<TSharedPtr<FJsonValue>> Rows;

    if (Infos.Num() <= 256)

    {

        for (const TSharedPtr<FUICommandInfo>& Info : Infos)

        {

            if (!Info.IsValid()) { continue; }

            TSharedRef<FJsonObject> Row = MakeShared<FJsonObject>();

            const FUIAction* Action = Editor->GetToolkitCommands()->GetActionForCommand(Info);

            Row->SetStringField(TEXT("name"), Info->GetCommandName().ToString());

            Row->SetStringField(TEXT("label"), Info->GetLabel().ToString());

            Row->SetBoolField(TEXT("mapped_native_toolkit_action"), Action != nullptr);

            Row->SetBoolField(TEXT("execute_delegate_bound"), Action && Action->ExecuteAction.IsBound());

            Row->SetBoolField(TEXT("can_execute_delegate_bound"), Action && Action->CanExecuteAction.IsBound());
            if (Action)
            {
                // Only the exact three source-audited native editor contexts are
                // queried here. Their CanExecute predicates inspect selection,
                // sequence identity or raw-dirty state and do not edit assets.
                Row->SetBoolField(TEXT("native_can_execute"), Editor->GetToolkitCommands()->CanExecuteAction(Info.ToSharedRef()));
            }

            Rows.Add(MakeShared<FJsonValueObject>(Row));

        }

    }

    LastCommands->SetArrayField(TEXT("commands"), Rows);

    LastCommands->SetStringField(TEXT("scope"), TEXT("Actual native toolkit command bindings and source-audited native CanExecute predicates for the three expected editor contexts. No Execute or authoring action is invoked."));

    return Infos.Num() > 0 && Infos.Num() <= 256;

}

void SaveState(const FString& Action, bool bActionSucceeded, const FString& Detail)

{

    TSharedRef<FJsonObject> State = MakeShared<FJsonObject>();

    State->SetNumberField(TEXT("schema_version"), 1);

    State->SetNumberField(TEXT("serial"), static_cast<double>(++ReportSerial));

    State->SetNumberField(TEXT("engine_frame"), static_cast<double>(GFrameCounter));

    State->SetStringField(TEXT("utc"), FDateTime::UtcNow().ToIso8601());

    State->SetStringField(TEXT("action"), Action);

    State->SetBoolField(TEXT("action_succeeded"), bActionSucceeded);

    State->SetStringField(TEXT("detail"), Detail);

    if (LastMenu.IsValid()) { State->SetObjectField(TEXT("context_menu"), LastMenu); }

    if (LastCapture.IsValid()) { State->SetObjectField(TEXT("capture"), LastCapture); }

    if (LastCommands.IsValid()) { State->SetObjectField(TEXT("native_command_bindings"), LastCommands); }

    State->SetStringField(TEXT("scope"), TEXT("Normal native Persona routing/UI/preview observation only. No asset saves, cooked-authoring claim, animation baking, skeleton reassignment or retail-runtime claim."));

    UObject* Asset = ActiveAsset.Get();

    State->SetStringField(TEXT("asset"), GetPathNameSafe(Asset));

    State->SetBoolField(TEXT("owned_asset"), Asset && Owns(Asset));

    State->SetBoolField(TEXT("asset_package_dirty"), Asset && Asset->GetOutermost()->IsDirty());

    State->SetStringField(TEXT("expected_editor"), ExpectedEditor(Asset));
    if (UAnimSequence* Sequence = Cast<UAnimSequence>(Asset))
    {
        const int32 RawTracks = Sequence->GetRawAnimationData().Num();
        const int32 RawMap = Sequence->GetRawTrackToSkeletonMapTable().Num();
        State->SetNumberField(TEXT("raw_animation_tracks"), RawTracks);
        State->SetNumberField(TEXT("raw_track_map_entries"), RawMap);
        State->SetBoolField(TEXT("has_native_raw_animation_data"), RawTracks > 0 && RawTracks == RawMap);
        State->SetStringField(TEXT("raw_capability_scope"), TEXT("Read-only original native arrays; restoring Persona does not reconstruct stripped editor raw tracks."));
    }

    UAssetEditorSubsystem* Subsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();

    IAssetEditorInstance* Instance = Asset ? Subsystem->FindEditorForAsset(Asset, false) : nullptr;

    State->SetStringField(TEXT("editor_name"), Instance ? Instance->GetEditorName().ToString() : FString());

    State->SetBoolField(TEXT("expected_editor_open"), Instance && Instance->GetEditorName().ToString() == ExpectedEditor(Asset));

    FAssetEditorToolkit* Editor = nullptr;

    TSharedPtr<IPersonaToolkit> Toolkit = GetPersona(Instance, Editor);

    State->SetBoolField(TEXT("persona_toolkit_valid"), Toolkit.IsValid());

    if (Toolkit.IsValid())

    {

        TSharedRef<IPersonaPreviewScene> Scene = Toolkit->GetPreviewScene();

        State->SetStringField(TEXT("persona_skeleton"), GetPathNameSafe(Toolkit->GetSkeleton()));

        if (USkeleton* Skeleton = Toolkit->GetSkeleton())

        {

            State->SetNumberField(TEXT("skeleton_ref_bones"), Skeleton->GetReferenceSkeleton().GetNum());

            State->SetNumberField(TEXT("skeleton_socket_count"), Skeleton->Sockets.Num());

        }

        State->SetStringField(TEXT("persona_animation"), GetPathNameSafe(Toolkit->GetAnimationAsset()));

        State->SetStringField(TEXT("preview_animation"), GetPathNameSafe(Scene->GetPreviewAnimationAsset()));

        State->SetNumberField(TEXT("selected_bone_index"), Scene->GetSelectedBoneIndex());

        int32 PostTicks = 0;

        for (const TSharedPtr<FObservedScene>& Observed : Scenes)

        {

            if (Observed->Scene.Pin() == Scene) { PostTicks = Observed->PostTicks; break; }

        }

        State->SetNumberField(TEXT("native_scene_post_ticks"), PostTicks);

        UDebugSkelMeshComponent* Component = Toolkit->GetPreviewMeshComponent();

        State->SetBoolField(TEXT("preview_component_valid"), IsValid(Component));

        if (IsValid(Component))

        {

            State->SetBoolField(TEXT("preview_component_registered"), Component->IsRegistered());

            State->SetStringField(TEXT("preview_component_class"), Component->GetClass()->GetPathName());

            const int32 MaterialCount = Component->GetNumMaterials();

            State->SetNumberField(TEXT("preview_material_count"), MaterialCount);

            State->SetBoolField(TEXT("preview_material_count_bounded"), MaterialCount >= 0 && MaterialCount <= 256);

            TArray<TSharedPtr<FJsonValue>> Materials;

            if (MaterialCount >= 0 && MaterialCount <= 256)

            {

                for (int32 Index = 0; Index < MaterialCount; ++Index)

                {

                    UMaterialInterface* Chosen = Component->GetMaterial(Index);

                    UMaterialInterface* Original = nullptr;

                    FName SlotName = NAME_None;

                    if (Component->SkeletalMesh && Component->SkeletalMesh->Materials.IsValidIndex(Index))

                    {

                        const FSkeletalMaterial& Slot = Component->SkeletalMesh->Materials[Index];

                        Original = Slot.MaterialInterface; SlotName = Slot.MaterialSlotName;

                    }

                    TSharedRef<FJsonObject> Material = MakeShared<FJsonObject>();

                    Material->SetNumberField(TEXT("index"), Index);

                    Material->SetStringField(TEXT("slot"), SlotName.ToString());

                    Material->SetStringField(TEXT("original_material"), GetPathNameSafe(Original));

                    Material->SetStringField(TEXT("original_class"), Original ? Original->GetClass()->GetPathName() : FString());

                    Material->SetStringField(TEXT("chosen_material"), GetPathNameSafe(Chosen));

                    Material->SetStringField(TEXT("chosen_class"), Chosen ? Chosen->GetClass()->GetPathName() : FString());

                    Material->SetBoolField(TEXT("component_material_differs_from_original"), Chosen != Original);

                    Materials.Add(MakeShared<FJsonValueObject>(Material));

                }

            }

            State->SetArrayField(TEXT("preview_component_materials"), Materials);

            State->SetStringField(TEXT("preview_mesh"), GetPathNameSafe(Component->SkeletalMesh));

            State->SetNumberField(TEXT("preview_world_time"), Component->GetWorld() ? Component->GetWorld()->GetTimeSeconds() : -1.0);

            bool bLocalFinite = false, bComponentFinite = false;

            const TArray<FTransform>& Local = Component->GetBoneSpaceTransforms();

            const TArray<FTransform>& ComponentSpace = Component->GetComponentSpaceTransforms();

            State->SetNumberField(TEXT("local_pose_count"), Local.Num());

            State->SetNumberField(TEXT("component_pose_count"), ComponentSpace.Num());

            State->SetStringField(TEXT("local_pose_md5"), PoseDigest(Local, bLocalFinite));

            State->SetStringField(TEXT("component_pose_md5"), PoseDigest(ComponentSpace, bComponentFinite));

            State->SetBoolField(TEXT("all_pose_transforms_finite_normalized"), bLocalFinite && bComponentFinite);

            UAnimInstance* ActiveInstance = Component->GetAnimInstance();
            State->SetStringField(TEXT("active_anim_instance"), GetPathNameSafe(ActiveInstance));
            State->SetStringField(TEXT("active_anim_instance_outer"), ActiveInstance ? GetPathNameSafe(ActiveInstance->GetOuter()) : FString());
            State->SetBoolField(TEXT("active_anim_instance_outer_matches_component"), ActiveInstance && ActiveInstance->GetOuter() == Component);
            State->SetBoolField(TEXT("active_anim_instance_component_matches"), ActiveInstance && ActiveInstance->GetSkelMeshComponent() == Component);
            if (IsValid(Component->PreviewInstance))

            {

                State->SetStringField(TEXT("preview_instance"), Component->PreviewInstance->GetPathName());
                State->SetStringField(TEXT("preview_instance_class"), Component->PreviewInstance->GetClass()->GetPathName());
                State->SetStringField(TEXT("preview_instance_outer"), GetPathNameSafe(Component->PreviewInstance->GetOuter()));
                State->SetBoolField(TEXT("preview_instance_outer_matches_component"), Component->PreviewInstance->GetOuter() == Component);
                State->SetBoolField(TEXT("preview_instance_component_matches"), Component->PreviewInstance->GetSkelMeshComponent() == Component);
                State->SetBoolField(TEXT("preview_instance_matches_active_instance"), ActiveInstance == Component->PreviewInstance);
                State->SetNumberField(TEXT("native_animation_time"), Component->PreviewInstance->GetCurrentTime());

                State->SetBoolField(TEXT("native_animation_playing"), Component->PreviewInstance->IsPlaying());

                State->SetStringField(TEXT("native_animation_asset"), GetPathNameSafe(Component->PreviewInstance->GetAnimationAsset()));

            }

        }

        TArray<TSharedPtr<FJsonValue>> Tabs;

        const TCHAR* TabNames[] = { TEXT("SkeletonTreeView"),TEXT("Viewport"),TEXT("DetailsTab"),TEXT("AdvancedPreviewTab"),TEXT("AnimAssetPropertiesTab"),TEXT("SequenceBrowser"),TEXT("Document"),TEXT("CurveEditor"),TEXT("SkeletonAnimNotifies"),TEXT("AnimCurveViewerTab"),TEXT("SkeletonSlotNames"),TEXT("AnimMontageSections"),TEXT("RetargetManager"),TEXT("MorphTargetsTab"),TEXT("ControlRigMappingWindow") };

        TSharedPtr<FTabManager> Manager = Editor->GetTabManager();

        for (const TCHAR* TabName : TabNames)

        {

            TSharedRef<FJsonObject> Tab = MakeShared<FJsonObject>();

            const FName Id(TabName);

            Tab->SetStringField(TEXT("id"), TabName);

            Tab->SetBoolField(TEXT("registered"), Manager.IsValid() && Manager->HasTabSpawner(Id));

            Tab->SetBoolField(TEXT("live"), Manager.IsValid() && Manager->FindExistingLiveTab(FTabId(Id)).IsValid());

            Tabs.Add(MakeShared<FJsonValueObject>(Tab));

        }

        State->SetArrayField(TEXT("tabs"), Tabs);
        if (TSharedPtr<SDockTab> ViewportTab = Manager.IsValid() ? Manager->FindExistingLiveTab(FTabId(FName(TEXT("Viewport")))) : nullptr)
        {
            int32 WidgetBudget = 4096;
            if (TSharedPtr<IPersonaViewport> Widget = FindPersonaViewport(ViewportTab->GetContent(), 0, WidgetBudget))
            { State->SetObjectField(TEXT("viewport_render"), ViewportTelemetry(Widget->GetViewportClient())); }
        }


        State->SetBoolField(TEXT("animation_browser_valid"), Instance->GetEditorName() == FName(TEXT("AnimationEditor")) && static_cast<IAnimationEditor*>(Instance)->GetAssetBrowser() != nullptr);

    }

    const FString Directory = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("PersonaOwnedProbe"));

    IFileManager::Get().MakeDirectory(*Directory, true);

    FString Text;

    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Text);

    FJsonSerializer::Serialize(State, Writer);

    const bool bWritten = FFileHelper::SaveStringToFile(Text, *FPaths::Combine(Directory, TEXT("LatestState.json")));

    if (!bWritten) { UE_LOG(LogRebirthPersonaOwnedProbe, Error, TEXT("Failed to write owned Persona state.")); }

    UE_LOG(LogRebirthPersonaOwnedProbe, Display, TEXT("PersonaProbe action=%s succeeded=%d detail=%s asset=%s"), *Action, bActionSucceeded, *Detail, *GetPathNameSafe(Asset));

}

void Run(const TArray<FString>& Args)

{

    if (!IsOwnedProcess()) { return; }

    if (Args.Num() == 0) { SaveState(TEXT("invalid"), false, TEXT("Expected open <loaded path>|snapshot|assetdetails|menu|frame <front/threequarter>|capture <label>|mesh <loaded path>|bone <name>|clearbone|play|pause|seek <seconds>|tab <id>|close.")); return; }

    const FString Action = Args[0].ToLower();

    UAssetEditorSubsystem* Subsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();

    if (Action == TEXT("open") && Args.Num() == 2)

    {

        UObject* Object = FindObject<UObject>(nullptr, *Args[1]);

        if (!IsValid(Object) || Object->HasAnyFlags(RF_NeedLoad | RF_NeedPostLoad) || ExpectedEditor(Object).IsEmpty())

        { SaveState(Action, false, TEXT("Only already loaded valid original AnimSequence, Skeleton or SkeletalMesh inputs are accepted.")); return; }

        if (Subsystem->FindEditorForAsset(Object, false))

        { SaveState(Action, false, TEXT("An editor already owns this asset; this probe will not close or reuse an unowned window.")); return; }

        if (!RestoreOwnedCameraClamp(TEXT("new_editor"))) { SaveState(Action, false, TEXT("Prior owned camera controller changed; restore refused.")); return; }

        ActiveAsset = Object; OwnedAssets.AddUnique(Object); LastMenu.Reset(); LastCapture.Reset(); LastCommands.Reset(); LastFraming.Reset();
        if (ViewObserver.IsValid()) { ViewObserver->ExpectedViewport = nullptr; }

        SaveState(TEXT("open_begin"), true, TEXT("Calling normal AssetEditorSubsystem route."));

        const bool bOpened = Subsystem->OpenEditorForAsset(Object, EToolkitMode::Standalone, nullptr, false);

        SaveState(Action, bOpened, TEXT("Normal asset editor request returned.")); return;

    }

    UObject* Object = ActiveAsset.Get();

    if (!Object || !Owns(Object)) { SaveState(Action, false, TEXT("No owned active asset.")); return; }

    if (Action == TEXT("close"))

    {

        if (ViewObserver.IsValid()) { ViewObserver->ExpectedViewport = nullptr; }
        if (!RestoreOwnedCameraClamp(TEXT("close"))) { SaveState(Action, false, TEXT("Owned camera controller changed; restore refused.")); return; }
        const int32 Closed = Subsystem->CloseAllEditorsForAsset(Object);

        OwnedAssets.RemoveAll([Object](const TWeakObjectPtr<UObject>& Owned) { return Owned.Get() == Object; });

        SaveState(Action, Closed > 0, TEXT("Closed only editors opened by this owned probe.")); return;

    }

    IAssetEditorInstance* Instance = Subsystem->FindEditorForAsset(Object, false);

    FAssetEditorToolkit* Editor = nullptr;

    TSharedPtr<IPersonaToolkit> Toolkit = GetPersona(Instance, Editor);

    if (!Toolkit.IsValid()) { SaveState(Action, false, TEXT("The normal native Persona toolkit is unavailable.")); return; }

    TSharedRef<IPersonaPreviewScene> Scene = Toolkit->GetPreviewScene();

    UDebugSkelMeshComponent* Component = Toolkit->GetPreviewMeshComponent();

    if (Action == TEXT("snapshot") && Args.Num() == 1) { SaveState(Action, true, TEXT("Observed native editor state.")); return; }

    if (Action == TEXT("assetdetails") && Args.Num() == 1)

    { const bool bOK = InspectNativeCommandBindings(Editor); SaveState(Action, bOK, TEXT("Native toolkit command bindings and source-audited CanExecute capability inspected; no edit actions executed.")); return; }

    if (Action == TEXT("menu") && Args.Num() == 1)

    { const bool bOK = InspectMenu(Object); SaveState(Action, bOK, TEXT("Actual registered context menu entries inspected without execution.")); return; }

    if (Action == TEXT("frame") && Args.Num() == 2)
    { const bool bOK = FramePersona(Editor, *Toolkit, Args[1]); SaveState(Action, bOK, TEXT("Bounded live native viewport framing only; no asset edits or saved camera changes.")); return; }
    if (Action == TEXT("capture") && Args.Num() == 2)

    { const bool bOK = CapturePersona(Editor, *Toolkit, Args[1]); SaveState(Action, bOK, TEXT("Actual native Persona viewport capture, fixed owned Saved path.")); return; }

    if (Action == TEXT("mesh") && Args.Num() == 2)

    {

        USkeletalMesh* Mesh = FindObject<USkeletalMesh>(nullptr, *Args[1]);

        if (!IsValid(Mesh) || Mesh->HasAnyFlags(RF_NeedLoad | RF_NeedPostLoad)) { SaveState(Action, false, TEXT("Receiving mesh must already be loaded and valid.")); return; }

        if (Mesh->Skeleton != Toolkit->GetSkeleton()) { SaveState(Action, false, TEXT("First native Persona probe accepts only matching original skeleton identity; foreign mesh scene changes can prompt skeleton rebuilding.")); return; }

        Scene->SetPreviewMesh(Mesh);

        SaveState(Action, Scene->GetPreviewMesh() == Mesh, TEXT("Preview-scene-only mesh change. Toolkit setter is deliberately avoided because it can override its save flag for foreign skeletons.")); return;

    }

    if (Action == TEXT("bone") && Args.Num() == 2)

    {

        if (!IsValid(Component) || Component->GetBoneIndex(FName(*Args[1])) == INDEX_NONE) { SaveState(Action, false, TEXT("The genuine preview mesh has no such bone.")); return; }

        Scene->SetSelectedBone(FName(*Args[1]), ESelectInfo::Direct);

        SaveState(Action, Scene->GetSelectedBoneIndex() == Component->GetBoneIndex(FName(*Args[1])), TEXT("Native skeleton-tree/viewport bone selection path.")); return;

    }

    if (Action == TEXT("clearbone") && Args.Num() == 1)

    { Scene->ClearSelectedBone(); SaveState(Action, Scene->GetSelectedBoneIndex() == INDEX_NONE, TEXT("Native bone selection cleared.")); return; }

    if (Action == TEXT("tab") && Args.Num() == 2)

    {

        const FName Id(*Args[1]);

        const TSet<FName> Allowed = {FName(TEXT("SkeletonTreeView")),FName(TEXT("Viewport")),FName(TEXT("DetailsTab")),FName(TEXT("AdvancedPreviewTab")),FName(TEXT("AnimAssetPropertiesTab")),FName(TEXT("SequenceBrowser")),FName(TEXT("SkeletonAnimNotifies")),FName(TEXT("AnimCurveViewerTab")),FName(TEXT("SkeletonSlotNames")),FName(TEXT("RetargetManager")),FName(TEXT("MorphTargetsTab")),FName(TEXT("ControlRigMappingWindow"))};

        TSharedPtr<FTabManager> Manager = Editor->GetTabManager();

        const bool bAllowed = Allowed.Contains(Id) && Manager.IsValid() && Manager->HasTabSpawner(Id);

        const bool bOpened = bAllowed && Manager->TryInvokeTab(FTabId(Id)).IsValid();

        SaveState(Action, bOpened, TEXT("Invoked allowlisted native inspection tab.")); return;

    }

    if ((Action == TEXT("play") || Action == TEXT("pause") || Action == TEXT("seek")) && IsValid(Component) && IsValid(Component->PreviewInstance))

    {

        UAnimSequence* Sequence = Cast<UAnimSequence>(Component->PreviewInstance->GetAnimationAsset());

        if (!Sequence || Sequence->Notifies.Num() != 0) { SaveState(Action, false, TEXT("Owned playback fixture must be an original no-notify sequence; notify dispatch is outside this test.")); return; }

        if (Action == TEXT("seek") && Args.Num() == 2)

        {

            double Seconds = 0.0;

            if (!LexTryParseString(Seconds, *Args[1]) || !FMath::IsFinite(Seconds) || Seconds < 0.0 || Seconds > Sequence->SequenceLength)

            { SaveState(Action, false, TEXT("Seek must be finite and within the original sequence length.")); return; }

            Component->PreviewInstance->SetPosition(static_cast<float>(Seconds), false);

        }

        else if (Args.Num() == 1 && Action != TEXT("seek"))
        {
            if (Action == TEXT("play") && !RestoreOwnedCameraClamp(TEXT("play")))
            { SaveState(Action, false, TEXT("Owned camera controller changed; restore refused.")); return; }
            Component->PreviewInstance->SetPlaying(Action == TEXT("play"));
        }

        else { SaveState(Action, false, TEXT("Invalid playback arguments.")); return; }

        Scene->InvalidateViews();

        SaveState(Action, true, TEXT("Native preview instance control; no asset edits or explicit synthetic tick.")); return;

    }

    SaveState(Action, false, TEXT("Unsupported command or unavailable native preview instance."));

}

}

void Register()

{

    if (!IsOwnedProcess() || Command.IsValid()) { return; }

    FPersonaModule& Persona = FModuleManager::LoadModuleChecked<FPersonaModule>(TEXT("Persona"));

    SceneCreatedHandle = Persona.OnPreviewSceneCreated().AddStatic(&ObserveScene);
    ViewObserver = FSceneViewExtensions::NewExtension<FOwnedPersonaViewObserver>();

    Command = MakeUnique<FAutoConsoleCommand>(TEXT("Rebirth.PersonaProbe"), TEXT("Owned native Persona test: open <loaded path>|snapshot|assetdetails|menu|frame <front/threequarter>|capture <label>|mesh <loaded path>|bone <name>|clearbone|play|pause|seek <seconds>|tab <id>|close. Writes Saved/PersonaOwnedProbe/LatestState.json."), FConsoleCommandWithArgsDelegate::CreateStatic(&Run));

}

void Unregister()

{

    RestoreOwnedCameraClamp(TEXT("unregister"));
    if (CameraClampExpiryHandle.IsValid()) { FTicker::GetCoreTicker().RemoveTicker(CameraClampExpiryHandle); CameraClampExpiryHandle.Reset(); }
    Command.Reset();
    if (ViewObserver.IsValid()) { ViewObserver->ExpectedViewport = nullptr; }
    FlushRenderingCommands(); ViewObserver.Reset(); LastFraming.Reset();

    if (FPersonaModule* Persona = FModuleManager::GetModulePtr<FPersonaModule>(TEXT("Persona"))) { Persona->OnPreviewSceneCreated().Remove(SceneCreatedHandle); }

    for (const TSharedPtr<FObservedScene>& Observed : Scenes)

    {

        if (TSharedPtr<IPersonaPreviewScene> Scene = Observed->Scene.Pin()) { Scene->UnregisterOnPostTick(Observed.Get()); }

    }

    Scenes.Empty(); OwnedAssets.Empty(); ActiveAsset.Reset(); LastMenu.Reset(); LastCapture.Reset(); LastCommands.Reset();

}

}

