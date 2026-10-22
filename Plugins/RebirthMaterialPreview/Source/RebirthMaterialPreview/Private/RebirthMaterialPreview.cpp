#include "CoreMinimal.h"
#include "RebirthNiagaraVfx1LoadAdapter.h"
#include "RebirthCookLogFilter.h"
#include "RebirthCookedTextureSkip.h"
#include "RebirthDataObjectEditing.h"
#include "RebirthCharaSpecCheck.h"
#include "RebirthAssetConversion.h"
#include "RebirthBlueprintTools.h"
#include "RebirthGameReferences.h"
#include "EndDataObjectBase.h"
#include "RebirthDataObjectSerialization.h"
#include "RebirthCookedMaterialMetadata.h"
#include "RebirthCookedMaterialConversion.h"
#include "RebirthRecoveredSurfaces.h"
#include "RebirthPersonaOwnedProbe.h"
#include "RebirthMaterialOwnedProbe.h"
#include "RebirthPersonaPreviewSupport.h"
#include "RebirthSkeletonCompatibilityEditorLibrary.h"
#include "Modules/ModuleManager.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "IAssetTypeActions.h"
#include "AssetTypeActions_Base.h"
#include "AssetRegistry/AssetData.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimationAsset.h"
#include <cmath>
#include "Animation/AnimCurveTypes.h"
#include "Animation/RebirthSkeletonCompatibility.h"
#include "Misc/MemStack.h"
#include "Misc/SecureHash.h"
#include "Serialization/JsonReader.h"
#include "Animation/AnimSingleNodeInstance.h"
#include "Animation/AnimBoneCompressionCodec.h"
#include "Animation/AnimCompressionTypes.h"
#include "Animation/Skeleton.h"
#include "BoneContainer.h"
#include "HAL/PlatformProcess.h"
#include "PropertyCustomizationHelpers.h"
#include "Widgets/Input/SSlider.h"
#include "Components/DirectionalLightComponent.h"
#include "MaterialShared.h"
#include "HAL/PlatformTime.h"
#include "Engine/SkeletalMesh.h"
#include "Rendering/SkeletalMeshRenderData.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInterface.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "NiagaraScript.h"
#include "PreviewScene.h"
#include "EditorViewportClient.h"
#include "SEditorViewport.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Framework/Docking/TabManager.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"
#include "UObject/Package.h"
#include "HAL/IConsoleManager.h"
#include "Misc/MessageDialog.h"
#include "RebirthMaterialDiagnosticsLibrary.h"
#include "Widgets/Layout/SScrollBox.h"
#include "RebirthMaterialPreviewSafety.h"
#include "RebirthPreviewMaterialResolver.h"
#include "RebirthMaterialFamilySnapshot.h"
#include "RebirthSafeMaterialThumbnailRenderer.h"
#include "RebirthSafeSkeletalMeshThumbnailRenderer.h"
#include "ThumbnailRendering/ThumbnailManager.h"
#include "UObject/StrongObjectPtr.h"
#include "Factories/MaterialInstanceConstantFactoryNew.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "Misc/PackageName.h"
#include "ToolMenus.h"
#include "RebirthMaterialInstanceOverrides.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "Widgets/Layout/SSplitter.h"
#include "Misc/CoreDelegates.h"
#include "UObject/UObjectBase.h"
#include "SceneView.h"
#include "RebirthBonamikPreviewSession.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "Containers/UnrealString.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Misc/SecureHash.h"
#include "HAL/FileManager.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "ImageUtils.h"
#include "RenderingThread.h"
#include "UnrealClient.h"
#include "Editor.h"
#include "EditorUndoClient.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthPreview, Log, All);

namespace RebirthPreview
{
static bool RegisterMaterialCompanions()
{
    FString Error;
    const FString Manifest=FPaths::ProjectConfigDir()/TEXT("RebirthPreviewMaterialCompanions.json");
    const int64 Size=IFileManager::Get().FileSize(*Manifest);
    if (Size>=0)
    {
        FString JSON; TSharedPtr<FJsonObject> Root;
        const TArray<TSharedPtr<FJsonValue>>* Rules=nullptr;
        if (Size>1024*1024 || !FFileHelper::LoadFileToString(JSON,*Manifest) ||
            !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JSON),Root) || !Root.IsValid() ||
            !Root->HasTypedField<EJson::Number>(TEXT("schema")) || Root->GetNumberField(TEXT("schema"))!=1 ||
            !Root->TryGetArrayField(TEXT("rules"),Rules) || Rules->Num()>4096)
        { UE_LOG(LogRebirthPreview,Warning,TEXT("Preview companion manifest is invalid: %s"),*Manifest); }
        else
        {
            int32 Registered=0;
            for (const TSharedPtr<FJsonValue>& Entry:*Rules)
            {
                const TSharedPtr<FJsonObject>* Object=nullptr;
                RebirthPreviewMaterialResolver::FCompanionRule Rule;
                if (!Entry.IsValid() || !Entry->TryGetObject(Object) || !Object || !Object->IsValid() ||
                    !(*Object)->TryGetStringField(TEXT("original_object_path"),Rule.OriginalObjectPath) ||
                    !(*Object)->TryGetStringField(TEXT("preview_object_path"),Rule.PreviewObjectPath) ||
                    !(*Object)->TryGetStringField(TEXT("fidelity"),Rule.Fidelity) ||
                    !(*Object)->TryGetBoolField(TEXT("allow_uniform_only_children"),Rule.bAllowUniformOnlyChildren) ||
                    Rule.Fidelity.Len()>512 || !Rule.OriginalObjectPath.StartsWith(TEXT("/Game/")))
                { UE_LOG(LogRebirthPreview,Warning,TEXT("Invalid preview companion manifest entry."));continue; }
                if (RebirthPreviewMaterialResolver::RegisterCompanion(Rule,Error)) { ++Registered; }
                else { UE_LOG(LogRebirthPreview,Warning,TEXT("Preview companion registration rejected: %s (%s)"),*Rule.OriginalObjectPath,*Error); }
            }
            UE_LOG(LogRebirthPreview,Display,TEXT("Preview companion manifest registered=%d entries=%d"),Registered,Rules->Num());
        }
    }
    // Explicit project rules take priority; embedded rules fill only missing originals.
    #include "ExistingCompanionRegistrations.inl"
    return true;
}

static const FName PreviewTabId(TEXT("RebirthRuntimePreview"));
class SRuntimePreviewViewport;
static TWeakPtr<SRuntimePreviewViewport> OwnedBonamikProbeViewport;
static void RunBonamikOwnedProbe(const TArray<FString>& Arguments);
static TWeakPtr<SRuntimePreviewViewport> OwnedAnimationProbeViewport;
static void RunAnimationOwnedProbe(const TArray<FString>& Arguments);
static TWeakPtr<SRuntimePreviewViewport> OwnedMaterialProbeViewport;
static void RunMaterialOwnedProbe(const TArray<FString>& Arguments);

static bool IsCooked(const UObject* Object)
{
    if (!Object || !Object->GetOutermost())
    {
        return false;
    }
    const UPackage* Package = Object->GetOutermost();
    return Package->bIsCookedForEditor || Package->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly);
}

static bool NeedsProtectedEditor(UObject* Object)
{
    if (IsCooked(Object)) { return true; }
    if (UMaterialInterface* Material = Cast<UMaterialInterface>(Object))
    {
        const RebirthMaterialPreviewSafety::FResult Result = RebirthMaterialPreviewSafety::Evaluate(Material);
        return Result.bUsesCookedChain || !Result.bParentChainValid || Result.bHasUnsupportedRenderState;
    }
    return false;
}

class FRuntimePreviewClient final : public FEditorViewportClient
{
public:
    FRuntimePreviewClient(TSharedRef<FPreviewScene> Scene, const TSharedRef<SEditorViewport>& Widget)
        : FEditorViewportClient(nullptr, &Scene.Get(), Widget), OwnedScene(Scene)
    {
        SetViewMode(VMI_Lit);
        SetRealtime(true);
        SetIsSimulateInEditorViewport(true);
        EngineShowFlags.SetSelectionOutline(false);
        EngineShowFlags.SetGrid(true);
        DrawHelper.bDrawGrid = true;
        DrawHelper.bDrawPivot = false;
        ShowWidget(false);
        OverrideNearClipPlane(1.0f);
        SetViewLocation(FVector(300.0f, -300.0f, 160.0f));
        SetViewRotation(FRotator(-18.0f, 135.0f, 0.0f));
        SetLookAtLocation(FVector::ZeroVector);
    }

    void EnableCharacterStudioLighting()
    {
        if (bCharacterStudioLighting) { return; }
        // Match the already validated recovered-character studio, with no broad
        // source angles (the recovered direct-light shader assumes punctual light).
        UDirectionalLightComponent* Key=OwnedScene->DirectionalLight;
        Key->SetIntensity(3.0f);Key->LightSourceAngle=0.0f;Key->LightSourceSoftAngle=0.0f;
        Key->SetWorldRotation(FRotator(-35.0f,-35.0f,0.0f));Key->MarkRenderStateDirty();
        const FRotator Rotations[]={FRotator(-20.0f,135.0f,0.0f),FRotator(-45.0f,220.0f,0.0f)};
        const float Intensities[]={1.5f,2.0f};
        for (int32 Index=0;Index<2;++Index)
        {
            UDirectionalLightComponent* Light=NewObject<UDirectionalLightComponent>(GetTransientPackage(),NAME_None,RF_Transient);
            Light->SetMobility(EComponentMobility::Movable);Light->SetIntensity(Intensities[Index]);
            Light->LightSourceAngle=0.0f;Light->LightSourceSoftAngle=0.0f;
            OwnedScene->AddComponent(Light,FTransform(Rotations[Index]));
        }
        bCharacterStudioLighting=true; // FPreviewScene owns/GC-roots all three components.
    }
    bool IsCharacterStudioLightingEnabled() const { return bCharacterStudioLighting; }

    int32 NativeViewportTickCalls=0;
    virtual void Tick(float DeltaSeconds) override
    {
        ++NativeViewportTickCalls;
        if (!FMath::IsFinite(DeltaSeconds) || DeltaSeconds < 0.0f)
        {
            if (BonamikSession.IsValid()) { BonamikSession->ResetSimulation(); }
            bBonamikEnabled = false;
            BonamikStatus = TEXT("Custom Bonamik preview stopped after an invalid viewport timestep.");
            return;
        }
        // Registration can change while playback is paused. Stop foreign playback
        // on the next real viewport frame without waiting for the user to press Play.
        if (USkeletalMeshComponent* Animated=AnimationComponent.Get())
        {
            UAnimSequence* Sequence=AnimationSequence.Get();
            if (Sequence && (!Animated->SkeletalMesh || !Animated->SkeletalMesh->Skeleton ||
                !Animated->SkeletalMesh->Skeleton->IsCompatible(Sequence->GetSkeleton())))
            { TickAnimationPreview(0.0f); }
        }
        FEditorViewportClient::Tick(DeltaSeconds);
        if (bPlaying && !GIntraFrameDebuggingGameThread && PreviewScene && IsRealtime())
        {
            // A backgrounded editor or shader stall may deliver a long frame.
            // Discard excess preview time explicitly, retaining the strict session API.
            const float BoundedDeltaSeconds = FMath::Min(DeltaSeconds, 0.1f);
            PreviewScene->GetWorld()->Tick(LEVELTICK_All, BoundedDeltaSeconds);
            if (AnimationComponent.IsValid())
            {
                TickAnimationPreview(BoundedDeltaSeconds);
                AnimationDroppedSeconds += DeltaSeconds-BoundedDeltaSeconds;
            }
            // The reference pose is unsimulated input. Never feed last frame's
            // modified component bone transforms back into the physics session.
            if (bBonamikEnabled && BonamikSession.IsValid() && BonamikSession->IsReady())
            {
                if (!BonamikSession->TickAndApply(BoundedDeltaSeconds, BonamikSession->GetReferenceComponentPose()))
                {
                    bBonamikEnabled = false;
                    BonamikSession->ResetSimulation();
                    BonamikStatus = TEXT("Custom Bonamik preview stopped after invalid pose or component transform; reset or enable it to retry.");
                    UE_LOG(LogRebirthPreview, Warning, TEXT("BonamikPreviewStopped reason=invalid_runtime_input"));
                }
                else
                {
                    ++BonamikAppliedFrames;
                    BonamikAppliedSeconds += BoundedDeltaSeconds;
                    if (DeltaSeconds > BoundedDeltaSeconds)
                    {
                        ++BonamikDroppedTickCount;
                        BonamikDroppedSeconds += DeltaSeconds - BoundedDeltaSeconds;
                    }
                }
            }
        }
    }

    virtual FSceneView* CalcSceneView(FSceneViewFamily* ViewFamily, const EStereoscopicPass StereoPass = eSSP_FULL) override
    {
        FSceneView* View = FEditorViewportClient::CalcSceneView(ViewFamily, StereoPass);
        if (View && ViewFamily && ViewDiagnosticCount < 8 &&
            (LastAntiAliasingMethod != static_cast<int32>(View->AntiAliasingMethod) ||
             LastFamilyRealtime != static_cast<int32>(ViewFamily->bRealtimeUpdate)))
        {
            LastAntiAliasingMethod = static_cast<int32>(View->AntiAliasingMethod);
            LastFamilyRealtime = static_cast<int32>(ViewFamily->bRealtimeUpdate);
            ++ViewDiagnosticCount;
            const IConsoleVariable* Quality = IConsoleManager::Get().FindConsoleVariable(TEXT("r.PostProcessAAQuality"));
            UE_LOG(LogRebirthPreview, Display, TEXT("PreviewViewDiagnostics actual_aa=%d family_realtime=%d temporal_aa_flag=%d aa_flag=%d aa_quality=%d"),
                LastAntiAliasingMethod, LastFamilyRealtime, EngineShowFlags.TemporalAA, EngineShowFlags.AntiAliasing,
                Quality ? Quality->GetInt() : -1);
        }
        if (View && bCharacterStudioLighting)
        {
            // Same manual exposure as the validated real-character capture scene.
            View->FinalPostProcessSettings.bOverride_AutoExposureMethod=true;
            View->FinalPostProcessSettings.AutoExposureMethod=AEM_Manual;
            View->FinalPostProcessSettings.bOverride_AutoExposureBias=true;
            View->FinalPostProcessSettings.AutoExposureBias=0.0f;
            View->FinalPostProcessSettings.bOverride_AutoExposureApplyPhysicalCameraExposure=true;
            View->FinalPostProcessSettings.AutoExposureApplyPhysicalCameraExposure=false;
        }
        return View;
    }

    void InitializeBonamik(UPoseableMeshComponent* Component)
    {
        ClearBonamik();
        TArray<USQEX_BonamikAsset*> Assets;
        FRebirthBonamikPreviewSession::FindLoadedAssets(Component ? Component->SkeletalMesh : nullptr, Assets);
        if (Assets.Num() != 1)
        {
            BonamikStatus = Assets.Num() == 0
                ? TEXT("Bonamik preview unavailable: no loaded Bonamik asset is attached to this mesh.")
                : TEXT("Bonamik preview unavailable: multiple attached Bonamik assets require explicit selection.");
            return;
        }
        BonamikSession = MakeUnique<FRebirthBonamikPreviewSession>();
        if (!BonamikSession->Initialize(Component, Assets[0], BonamikStatus))
        {
            BonamikSession.Reset();
            UE_LOG(LogRebirthPreview, Warning, TEXT("BonamikPreviewUnavailable reason=%s"), *BonamikStatus);
            return;
        }
        bBonamikEnabled = true; // Matches the existing automatically playing preview.
        UE_LOG(LogRebirthPreview, Display, TEXT("BonamikPreviewReady asset=%s status=%s"), *GetPathNameSafe(Assets[0]), *BonamikStatus);
    }

    void ClearBonamik()
    {
        bBonamikEnabled = false;
        if (BonamikSession.IsValid()) { BonamikSession->Clear(); }
        BonamikSession.Reset();
        BonamikStatus.Reset();
        BonamikAppliedFrames = 0;
        BonamikAppliedSeconds = 0.0;
        BonamikDroppedTickCount = 0;
        BonamikDroppedSeconds = 0.0;
    }

    void ToggleBonamik()
    {
        if (!IsBonamikReady()) { return; }
        BonamikSession->ResetSimulation(); // Disabling restores the unsimulated pose.
        bBonamikEnabled = !bBonamikEnabled;
        BonamikStatus = BonamikSession->GetStatus();
        UE_LOG(LogRebirthPreview, Display, TEXT("BonamikPreviewToggled enabled=%d"), bBonamikEnabled ? 1 : 0);
    }

    void ResetBonamik()
    {
        if (BonamikSession.IsValid())
        {
            BonamikSession->ResetSimulation();
            BonamikStatus = BonamikSession->GetStatus();
        }
    }

    bool IsBonamikReady() const { return BonamikSession.IsValid() && BonamikSession->IsReady(); }
    bool IsBonamikEnabled() const { return bBonamikEnabled; }
    const FRebirthBonamikPreviewSession* GetBonamikSession() const { return BonamikSession.Get(); }
    FString GetBonamikStatus() const
    {
        if (!IsBonamikReady()) { return BonamikStatus; }
        return BonamikStatus + (bBonamikEnabled
            ? (bPlaying ? TEXT(" Simulation running.") : TEXT(" Simulation paused."))
            : TEXT(" Simulation disabled; unsimulated pose restored."));
    }

    #include "RebirthAnimationPreviewClient.inl"

    bool bPlaying = true;
    int32 BonamikAppliedFrames = 0;
    double BonamikAppliedSeconds = 0.0;
    int32 BonamikDroppedTickCount = 0;
    double BonamikDroppedSeconds = 0.0;
private:
    TUniquePtr<FRebirthBonamikPreviewSession> BonamikSession;
    bool bBonamikEnabled = false;
    FString BonamikStatus;
    TSharedRef<FPreviewScene> OwnedScene;
    int32 LastAntiAliasingMethod = -1;
    int32 LastFamilyRealtime = -1;
    int32 ViewDiagnosticCount = 0;
    bool bCharacterStudioLighting=false;
};

class SRuntimePreviewViewport final : public SEditorViewport
{
public:
    SLATE_BEGIN_ARGS(SRuntimePreviewViewport) {}
        SLATE_ARGUMENT(UObject*, Asset)
    SLATE_END_ARGS()

    void Construct(const FArguments& Arguments)
    {
        Scene = MakeShared<FPreviewScene>(FPreviewScene::ConstructionValues().SetTransactional(false)
            .SetCreatePhysicsScene(!Cast<UAnimSequence>(Arguments._Asset)).ShouldSimulatePhysics(false));
        SEditorViewport::Construct(SEditorViewport::FArguments());
        SetAsset(Arguments._Asset);
        if (UMaterialInterface* Material=Cast<UMaterialInterface>(Arguments._Asset))
        {
            EditedMaterialSource.Reset(Material);
            MaterialPropertyHandle=FCoreUObjectDelegates::OnObjectPropertyChanged.AddSP(this, &SRuntimePreviewViewport::OnMaterialSourceChanged);
        }
        if (FParse::Param(FCommandLine::Get(), TEXT("RebirthMaterialOwnedProbe")))
        {
            OwnedMaterialProbeAssetPath = GetPathNameSafe(Arguments._Asset);
            OwnedMaterialProbeViewport = SharedThis(this);
        }
        if (FParse::Param(FCommandLine::Get(),TEXT("RebirthAnimationOwnedPreviewProbe")) && Cast<UAnimSequence>(Arguments._Asset))
        { OwnedAnimationProbeViewport=SharedThis(this); }
        if (FParse::Param(FCommandLine::Get(), TEXT("RebirthBonamikOwnedPreviewProbe")) && Cast<USkeletalMesh>(Arguments._Asset))
        {
            OwnedBonamikProbeAssetPath = GetPathNameSafe(Arguments._Asset);
            OwnedBonamikProbeViewport = SharedThis(this);
        }
    }

    virtual ~SRuntimePreviewViewport() override
    {
        FCoreUObjectDelegates::OnObjectPropertyChanged.Remove(MaterialPropertyHandle);
        CancelSkeletalShaderRetry();
        CancelMaterialShaderRetry();
        ClearComponent();
        if (Client.IsValid())
        {
            Client->Viewport = nullptr;
        }
    }

    FReply TogglePlayback()
    {
        if (IsAnimationMode() && !PreviewClient->IsAnimationReady())
        { PreviewClient->bPlaying=false;Invalidate();return FReply::Handled(); }
        PreviewClient->bPlaying = !PreviewClient->bPlaying;
        if (IsAnimationMode()) { bAnimationWantsPlay=PreviewClient->bPlaying; }
        Invalidate();
        return FReply::Handled();
    }

    FText PlaybackLabel() const
    {
        return FText::FromString(PreviewClient.IsValid() && PreviewClient->bPlaying ? TEXT("Pause") : TEXT("Play"));
    }

    FReply ToggleBonamik()
    {
        PreviewClient->ToggleBonamik();
        Invalidate();
        return FReply::Handled();
    }

    FText BonamikLabel() const
    {
        return FText::FromString(PreviewClient.IsValid() && PreviewClient->IsBonamikEnabled()
            ? TEXT("Bonamik: On") : TEXT("Bonamik: Off"));
    }

    EVisibility BonamikVisibility() const
    {
        return PreviewClient.IsValid() && PreviewClient->IsBonamikReady()
            ? EVisibility::Visible : EVisibility::Collapsed;
    }

    FReply Restart()
    {
        if (IsAnimationMode())
        {
            PreviewClient->RestartAnimationPreview();
            bAnimationWantsPlay=PreviewClient->IsAnimationReady() && PreviewClient->bPlaying;
            Invalidate();return FReply::Handled();
        }
        PreviewClient->ResetBonamik();
        PreviewClient->RestartAnimationPreview();
        if (IsAnimationMode()) { bAnimationWantsPlay=true; }
        if (Cascade)
        {
            Cascade->ResetParticles(true);
            Cascade->ActivateSystem(true);
        }
        if (Niagara)
        {
            Niagara->ReinitializeSystem();
            Niagara->Activate(true);
        }
        PreviewClient->bPlaying = true;
        Invalidate();
        return FReply::Handled();
    }

    FReply Focus()
    {
        OwnedAnimationFocusMode=TEXT("full");
        if (IsAnimationMode() && PreviewClient.IsValid() && PreviewClient->IsAnimationReady())
        {
            FBox Bounds(ForceInit),BoneBounds(ForceInit);int32 RequiredCount=0;
            if (PreviewClient->GetAnimationFramingBounds(Bounds,BoneBounds,RequiredCount))
            {
                AnimationFocusBefore=PreviewClient->GetViewLocation().ToString();
                const FRotator Rotation=PreviewClient->GetViewRotation();
                const FRotationMatrix Basis(Rotation);
                const FVector Forward=Basis.GetScaledAxis(EAxis::X),Right=Basis.GetScaledAxis(EAxis::Y),Up=Basis.GetScaledAxis(EAxis::Z);
                const FIntPoint Size=PreviewClient->Viewport?PreviewClient->Viewport->GetSizeXY():FIntPoint::ZeroValue;
                const float Aspect=Size.X>0 && Size.Y>0?float(Size.X)/float(Size.Y):16.0f/9.0f;
                const float TanHalfH=FMath::Tan(FMath::DegreesToRadians(FMath::Clamp(PreviewClient->ViewFOV,10.0f,150.0f)*0.5f));
                const float TanHalfV=TanHalfH/Aspect;
                const FVector Center=Bounds.GetCenter();float Distance=10.0f;
                // Fit every padded world-space AABB corner to the actual horizontal
                // FOV and viewport aspect, retaining the user's viewing direction.
                for (int32 Corner=0;Corner<8;++Corner)
                {
                    const FVector Point((Corner&1)?Bounds.Max.X:Bounds.Min.X,(Corner&2)?Bounds.Max.Y:Bounds.Min.Y,(Corner&4)?Bounds.Max.Z:Bounds.Min.Z);
                    const FVector Relative=Point-Center;const float Depth=FVector::DotProduct(Relative,Forward);
                    Distance=FMath::Max(Distance,FMath::Abs(FVector::DotProduct(Relative,Right))/TanHalfH-Depth);
                    Distance=FMath::Max(Distance,FMath::Abs(FVector::DotProduct(Relative,Up))/TanHalfV-Depth);
                }
                Distance+=FMath::Max(10.0f,Bounds.GetExtent().Size()*0.05f);
                PreviewClient->SetLookAtLocation(Center,false);
                PreviewClient->SetViewRotation(Rotation);
                PreviewClient->SetViewLocation(Center-Forward*Distance);
                AnimationFocusAfter=PreviewClient->GetViewLocation().ToString();
                bAnimationFocusedEvaluatedPose=true;
                UE_LOG(LogRebirthPreview,Display,TEXT("AnimationPoseFraming required=%d min=%s max=%s before=%s after=%s fov=%.3f aspect=%.3f"),
                    RequiredCount,*Bounds.Min.ToString(),*Bounds.Max.ToString(),*AnimationFocusBefore,*AnimationFocusAfter,PreviewClient->ViewFOV,Aspect);
                Invalidate();return FReply::Handled();
            }
        }
        FBox Bounds(FVector(-100.0f), FVector(100.0f));
        if (Component && Component->Bounds.GetBox().IsValid)
        {
            Bounds = Component->Bounds.GetBox();
            // An empty or absurd cooked fixed bound must not send the camera into space.
            if (Bounds.GetExtent().GetMax() < 1.0f || Bounds.GetExtent().GetMax() > 100000.0f)
            {
                Bounds = FBox(FVector(-250.0f), FVector(250.0f));
            }
        }
        PreviewClient->FocusViewportOnBox(Bounds, true);
        Invalidate();
        return FReply::Handled();
    }

    FString RunOwnedBonamikProbeCommand(const TArray<FString>& Arguments);
    FString RunOwnedMaterialProbeCommand(const TArray<FString>& Arguments);
    void RefreshEditedMaterial(UMaterialInterface* Material)
    {
        if (IsValid(Material)) { SetAsset(Material); Invalidate(); }
    }

    bool FocusAnimationFace()
    {
        USkeletalMeshComponent* Mesh=Cast<USkeletalMeshComponent>(Component);
        if (!PreviewClient.IsValid() || !PreviewClient->IsAnimationReady() || !Mesh || !Mesh->SkeletalMesh) { return false; }
        const int32 Head=Mesh->SkeletalMesh->RefSkeleton.FindBoneIndex(TEXT("C_Head_a"));
        const auto& Pose=Mesh->GetComponentSpaceTransforms();
        if (!Pose.IsValidIndex(Head) || !Pose[Head].IsValid()) { return false; }
        const FVector Center=Mesh->GetComponentTransform().TransformPosition(Pose[Head].GetTranslation())+FVector(0.0f,0.0f,8.0f);
        if (Center.ContainsNaN()) { return false; }
        const FIntPoint Size=PreviewClient->Viewport?PreviewClient->Viewport->GetSizeXY():FIntPoint(16,9);
        const double Aspect=(Size.X>0 && Size.Y>0)?double(Size.X)/Size.Y:16.0/9.0;
        const double TanVertical=FMath::Tan(FMath::DegreesToRadians(PreviewClient->ViewFOV*0.5f))/Aspect;
        if (!FMath::IsFinite(TanVertical) || TanVertical<=0.001) { return false; }
        const float Distance=FMath::Max(90.0f,float(30.0/TanVertical*1.3));
        const FVector Location=Center+FVector(Distance,0.0f,5.0f);
        PreviewClient->SetLookAtLocation(Center);PreviewClient->SetViewLocation(Location);
        PreviewClient->SetViewRotation((Center-Location).Rotation());
        OwnedAnimationFocusMode=TEXT("face");Invalidate();return true;
    }

    FText AnimationRootAlignmentLabel() const
    { return FText::FromString(bAnimationRootAlignmentEnabled?TEXT("Root alignment: On"):TEXT("Root alignment: Off")); }
    bool SetAnimationRootAlignmentEnabled(bool bEnabled)
    {
        if (!IsAnimationMode() || !PreviewClient.IsValid()) { return false; }
        if (PreviewClient->IsAnimationReady())
        {
            FString Reason;
            if (!PreviewClient->SetAnimationRootAlignment(bEnabled,Reason))
            { PreviewClient->StopAnimationForGuard(Reason);Invalidate();return false; }
        }
        bAnimationRootAlignmentEnabled=bEnabled;
        if (PreviewClient->IsAnimationReady()) { Focus(); }
        Invalidate();return true;
    }
    FReply ToggleAnimationRootAlignment()
    { SetAnimationRootAlignmentEnabled(!bAnimationRootAlignmentEnabled);return FReply::Handled(); }

    #include "RebirthAnimationPreviewViewport.inl"

    FText GetStatus() const
    {
        const FString BonamikStatus = PreviewClient.IsValid() ? PreviewClient->GetBonamikStatus() : FString();
        FString Result=BonamikStatus.IsEmpty()?Status:Status+TEXT("\n")+BonamikStatus;
        if (IsAnimationMode() && PreviewClient.IsValid() && !PreviewClient->GetAnimationRuntimeStatus().IsEmpty())
        { Result+=TEXT("\n")+PreviewClient->GetAnimationRuntimeStatus(); }
        return FText::FromString(Result);
    }

protected:
    virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override
    {
        PreviewClient = MakeShared<FRuntimePreviewClient>(Scene.ToSharedRef(), SharedThis(this));
        return PreviewClient.ToSharedRef();
    }

private:
    void OnMaterialSourceChanged(UObject* Object, FPropertyChangedEvent&)
    {
        if (Object==EditedMaterialSource.Get()) { RefreshEditedMaterial(EditedMaterialSource.Get()); }
    }
    void CancelMaterialShaderRetry()
    {
        if (TSharedPtr<FActiveTimerHandle> Timer = MaterialShaderRetryTimer.Pin()) { UnRegisterActiveTimer(Timer.ToSharedRef()); }
        MaterialShaderRetryTimer.Reset(); PendingMaterialAsset.Reset(); bMaterialShaderRetryPending = false;
    }
    void QueueMaterialShaderRetry(UMaterialInterface* Material)
    {
        if (!PendingMaterialAsset.IsValid()) { MaterialShaderRetryDeadline = FPlatformTime::Seconds() + 600.0; }
        PendingMaterialAsset.Reset(Material); bMaterialShaderRetryPending = true;
        if (!MaterialShaderRetryTimer.IsValid())
        { MaterialShaderRetryTimer = RegisterActiveTimer(0.2f, FWidgetActiveTimerDelegate::CreateSP(this, &SRuntimePreviewViewport::RetryMaterialShaders)); }
    }
    EActiveTimerReturnType RetryMaterialShaders(double, float)
    {
        UMaterialInterface* Material = PendingMaterialAsset.Get();
        if (!Material || FPlatformTime::Seconds() > MaterialShaderRetryDeadline)
        { MaterialShaderRetryTimer.Reset(); PendingMaterialAsset.Reset(); bMaterialShaderRetryPending = false; return EActiveTimerReturnType::Stop; }
        bMaterialShaderRetryPending = false;
        SetAsset(Material, true);
        if (bMaterialShaderRetryPending) { return EActiveTimerReturnType::Continue; }
        MaterialShaderRetryTimer.Reset(); PendingMaterialAsset.Reset(); return EActiveTimerReturnType::Stop;
    }
    void CancelSkeletalShaderRetry()
    {
        if (TSharedPtr<FActiveTimerHandle> Timer = SkeletalShaderRetryTimer.Pin())
        {
            UnRegisterActiveTimer(Timer.ToSharedRef());
        }
        SkeletalShaderRetryTimer.Reset();
        PendingSkeletalAsset.Reset();
        bSkeletalShaderRetryPending = false;
        SkeletalShaderRetryCount = 0;
        bWaitingForRecoveredCompilation = false;
        RecoveredShaderWaitStartedSeconds = 0.0;
        NextRecoveredShaderCheckSeconds = 0.0;
    }

    void QueueSkeletalShaderRetry(USkeletalMesh* SkeletalMesh, const FString& Reason, bool bRecoveredCompilation = false)
    {
        constexpr int32 MaxShaderInitializationRetries = 120;
        constexpr double MaxRecoveredCompilationWaitSeconds = 600.0;
        if (bRecoveredCompilation)
        {
            const double Now = FPlatformTime::Seconds();
            if (RecoveredShaderWaitStartedSeconds == 0.0) { RecoveredShaderWaitStartedSeconds = Now; }
            if (Now - RecoveredShaderWaitStartedSeconds >= MaxRecoveredCompilationWaitSeconds)
            {
                Status = TEXT("Recovered character shaders did not finish compiling within 600 seconds. No mesh was submitted; reopen the preview after compilation completes.");
                UE_LOG(LogRebirthPreview, Warning, TEXT("SkeletalPreviewBlocked asset=%s reason=%s timeout_seconds=600"), *GetPathNameSafe(SkeletalMesh), *Reason);
                return;
            }
            bWaitingForRecoveredCompilation = true;
            NextRecoveredShaderCheckSeconds = Now + 0.25;
        }
        if (!bRecoveredCompilation && SkeletalShaderRetryCount >= MaxShaderInitializationRetries)
        {
            Status = FString::Printf(TEXT("Skeletal preview unavailable after waiting for shader resource initialization: %s. No mesh was submitted to the renderer."), *Reason);
            UE_LOG(LogRebirthPreview, Warning, TEXT("SkeletalPreviewBlocked asset=%s reason=%s retries=%d"), *GetPathNameSafe(SkeletalMesh), *Reason, SkeletalShaderRetryCount);
            return;
        }
        PendingSkeletalAsset.Reset(SkeletalMesh);
        bSkeletalShaderRetryPending = true;
        Status = bRecoveredCompilation
            ? TEXT("Waiting for recovered character shaders to compile (up to 600 seconds). No mesh has been submitted to the renderer.")
            : FString::Printf(TEXT("Waiting for character shader resources to initialize (%d/%d). No mesh has been submitted to the renderer."), SkeletalShaderRetryCount, MaxShaderInitializationRetries);
        if (!SkeletalShaderRetryTimer.IsValid())
        {
            SkeletalShaderRetryTimer = RegisterActiveTimer(0.0f, FWidgetActiveTimerDelegate::CreateSP(this, &SRuntimePreviewViewport::RetrySkeletalShaders));
        }
    }

    EActiveTimerReturnType RetrySkeletalShaders(double, float)
    {
        USkeletalMesh* SkeletalMesh = PendingSkeletalAsset.Get();
        if (!IsValid(SkeletalMesh) || IsEngineExitRequested())
        {
            PendingSkeletalAsset.Reset();
            SkeletalShaderRetryTimer.Reset();
            bSkeletalShaderRetryPending = false;
            return EActiveTimerReturnType::Stop;
        }
        if (bWaitingForRecoveredCompilation && FPlatformTime::Seconds() < NextRecoveredShaderCheckSeconds)
        {
            return EActiveTimerReturnType::Continue;
        }
        if (!bWaitingForRecoveredCompilation) { ++SkeletalShaderRetryCount; }
        bWaitingForRecoveredCompilation = false;
        bSkeletalShaderRetryPending = false;
        // A new frame may finish queued resource initialization. Recheck every
        // slot through the same safety guard before creating a scene component.
        SetAsset(AnimationAsset.IsValid()?static_cast<UObject*>(AnimationAsset.Get()):static_cast<UObject*>(SkeletalMesh),true);
        if (bSkeletalShaderRetryPending)
        {
            return EActiveTimerReturnType::Continue;
        }
        PendingSkeletalAsset.Reset();
        SkeletalShaderRetryTimer.Reset();
        return EActiveTimerReturnType::Stop;
    }

    void ClearComponent()
    {
        // Clear/reset before the registered transient component is removed.
        if (PreviewClient.IsValid()) { PreviewClient->ClearBonamik(); PreviewClient->ClearAnimationPreview(); }
        if (Component && Scene.IsValid())
        {
            if (Cascade) { Cascade->DeactivateSystem(); }
            if (Niagara) { Niagara->DeactivateImmediate(); }
            Scene->RemoveComponent(Component);
            Component->DestroyComponent();
        }
        Component = nullptr;
        Cascade = nullptr;
        Niagara = nullptr;
    }

    void SetAsset(UObject* Asset, bool bSkeletalShaderRetry = false)
    {
        if (!bSkeletalShaderRetry)
        {
            CancelSkeletalShaderRetry();
            CancelMaterialShaderRetry();
        }
        ClearComponent();
        if (UAnimSequence* Sequence=Cast<UAnimSequence>(Asset))
        {
            AnimationAsset.Reset(Sequence);
            FString Reason;
            if (!CheckAnimationRequest(Reason))
            {
                PreviewClient->bPlaying=false;Status=Reason;
                UE_LOG(LogRebirthPreview,Display,TEXT("AnimationPreviewPendingOrBlocked clip=%s receiver=%s reason=%s"),
                    *Sequence->GetPathName(),*GetPathNameSafe(AnimationReceivingMesh.Get()),*Reason);
                return;
            }
            Asset=AnimationReceivingMesh.Get(); // Enter the SAME guarded skeletal material/geometry branch.
        }
        else if (!bSkeletalShaderRetry)
        { AnimationAsset.Reset();AnimationReceivingMesh.Reset(); }
        if (UMaterialInterface* Material = Cast<UMaterialInterface>(Asset))
        {
            const RebirthPreviewMaterialResolver::FResult Resolution = RebirthPreviewMaterialResolver::Resolve(Material, GetTransientPackage());
            if (!Resolution.Material)
            {
                Status = FString::Printf(TEXT("Material preview unavailable: %s"), *Resolution.Reason);
                UE_LOG(LogRebirthPreview, Warning, TEXT("MaterialPreviewBlocked asset=%s reason=%s"), *Material->GetPathName(), *Resolution.Reason);
                if (Resolution.bPendingShaderResources) { QueueMaterialShaderRetry(Material); }
                return;
            }
            UStaticMesh* Sphere = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Sphere.Sphere"));
            if (!Sphere)
            {
                Status = TEXT("The engine preview sphere is missing. The material was not changed.");
                return;
            }
            UStaticMeshComponent* Mesh = NewObject<UStaticMeshComponent>(GetTransientPackage(), NAME_None, RF_Transient);
            Mesh->SetStaticMesh(Sphere);
            Mesh->SetMaterial(0, Resolution.Material);
            Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            Component = Mesh;
            Scene->AddComponent(Mesh, FTransform::Identity);
            Status = Resolution.Fidelity;
            UE_LOG(LogRebirthPreview, Display, TEXT("MaterialPreviewReady original=%s rendered=%s fidelity=%s"),
                *Material->GetPathName(), *Resolution.Material->GetPathName(), *Resolution.Fidelity);
        }
        else if (USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(Asset))
        {
            const FSkeletalMeshRenderData* RenderData = SkeletalMesh->GetResourceForRendering();
            if (!RenderData || RenderData->LODRenderData.Num() == 0 || SkeletalMesh->RefSkeleton.GetNum() == 0)
            {
                Status = TEXT("This skeletal mesh has no loaded render LOD or reference skeleton.");
                return;
            }
            TArray<UMaterialInterface*> PreviewMaterials;
            bool bReconstructedMaterials = false;
            bool bRecoveredMaterials = false;
            for (const FSkeletalMaterial& Slot : SkeletalMesh->Materials)
            {
                const RebirthPreviewMaterialResolver::FResult Resolution = RebirthPreviewMaterialResolver::Resolve(Slot.MaterialInterface, GetTransientPackage());
                if (!Resolution.Material)
                {
                    if (Resolution.bPendingShaderResources) { QueueSkeletalShaderRetry(SkeletalMesh, Resolution.Reason, true); }
                    else { Status = FString::Printf(TEXT("Skeletal preview unavailable for material %s: %s"), *GetPathNameSafe(Slot.MaterialInterface), *Resolution.Reason); }
                    return;
                }
                if (!Resolution.Material->GetMaterial()->GetUsageByFlag(MATUSAGE_SkeletalMesh))
                {
                    Status = TEXT("The resolved material does not support skeletal meshes."); return;
                }
                bReconstructedMaterials |= !Resolution.bUsesOriginalResource;
                bRecoveredMaterials |= Resolution.Fidelity.StartsWith(TEXT("Recovered"));
                PreviewMaterials.Add(Resolution.Material);
            }
            if (bRecoveredMaterials && Scene->DirectionalLight)
            {
                // Recovered direct-light adapter is validated for zero-angle sunlight.
                Scene->DirectionalLight->LightSourceAngle = 0.0f;
                Scene->DirectionalLight->LightSourceSoftAngle = 0.0f;
                Scene->DirectionalLight->MarkRenderStateDirty();
            }
            PreviewClient->EnableCharacterStudioLighting();
            if (AnimationAsset.IsValid())
            {
                USkeletalMeshComponent* Mesh=NewObject<USkeletalMeshComponent>(GetTransientPackage(),NAME_None,RF_Transient);
                for (int32 Index=0;Index<PreviewMaterials.Num();++Index) { Mesh->SetMaterial(Index,PreviewMaterials[Index]); }
                Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
                Mesh->bDisableClothSimulation=true;Mesh->SetDisablePostProcessBlueprint(true);
                Mesh->bEnableUpdateRateOptimizations=false;
                Mesh->VisibilityBasedAnimTickOption=EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
                Mesh->SetAllowAnimCurveEvaluation(false);
                Mesh->SetSkeletalMesh(SkeletalMesh);Mesh->SetForcedLOD(1);
                Component=Mesh;Scene->AddComponent(Mesh,FTransform::Identity);
                Mesh->SetUpdateAnimationInEditor(true);
                if (!PreviewClient->InitializeAnimationPreview(Mesh,AnimationAsset.Get(),bAnimationWantsPlay,bAnimationRootAlignmentEnabled))
                { Status=TEXT("Native animation playback could not initialize; original assets are unchanged.");return; }
                Status=FString::Printf(TEXT("Original animation %s on %s. %s Original clips, skeletons and materials remain read-only."),
                    *AnimationAsset->GetName(),*SkeletalMesh->GetName(),bRecoveredMaterials
                    ? TEXT("Uses recovered Rebirth hair/eye shading and compatible body materials.")
                    : bReconstructedMaterials?TEXT("Uses compatible preview materials and game textures."):TEXT("Uses loaded native materials."));
                UE_LOG(LogRebirthPreview,Display,TEXT("AnimationPreviewReady clip=%s receiver=%s materials=%d bonamik=off"),
                    *AnimationAsset->GetPathName(),*SkeletalMesh->GetPathName(),PreviewMaterials.Num());
            }
            else
            {
                UPoseableMeshComponent* Mesh = NewObject<UPoseableMeshComponent>(GetTransientPackage(), NAME_None, RF_Transient);
                for (int32 Index = 0; Index < PreviewMaterials.Num(); ++Index) { Mesh->SetMaterial(Index, PreviewMaterials[Index]); }
                Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
                Mesh->SetSkeletalMesh(SkeletalMesh);Mesh->SetForcedLOD(1);
                Component = Mesh;Scene->AddComponent(Mesh, FTransform::Identity);
                PreviewClient->InitializeBonamik(Mesh);
                Status = bRecoveredMaterials
                    ? TEXT("Reference-pose preview with recovered Rebirth hair and/or eye shading. Direct lighting follows the game shaders; native indirect lighting and scattering still differ.")
                    : bReconstructedMaterials
                    ? TEXT("Reference-pose character preview with native compatibility materials and the game's textures. Shading is reconstructed; original cooked materials and parents are unchanged.")
                    : TEXT("Reference-pose character preview using the asset's loaded geometry and materials.");
            }
        }
        else if (UParticleSystem* System = Cast<UParticleSystem>(Asset))
        {
            Cascade = NewObject<UParticleSystemComponent>(GetTransientPackage(), NAME_None, RF_Transient);
            Cascade->bAutoActivate = false;
            Cascade->bAutoDestroy = false;
            Cascade->bTickInEditor = true;
            Cascade->SetTemplate(System);
            Component = Cascade;
            Scene->AddComponent(Cascade, FTransform::Identity);
            Cascade->ActivateSystem(true);
            Status = TEXT("Cooked Cascade runtime preview. Graph rebuilding and package saving are disabled in this window.");
        }
        else if (UNiagaraSystem* NiagaraSystem = Cast<UNiagaraSystem>(Asset))
        {
            // SetAsset/Activate/solo simulation were checked in this engine's NiagaraComponent.cpp.
            // They do not call RequestCompile. Never construct the Niagara graph editor/view model.
            if (NiagaraSystem->HasOutstandingCompilationRequests(true) || !NiagaraSystem->IsReadyToRun())
            {
                Status = TEXT("This cooked Niagara system has no ready runtime data or still has a compilation request. Preview was not activated; stripped graphs cannot be rebuilt. Check the Output Log and include its dependencies.");
                UE_LOG(LogRebirthPreview, Warning, TEXT("Refusing to activate Niagara without ready compiled data: %s"), *NiagaraSystem->GetPathName());
                return;
            }
            Niagara = NewObject<UNiagaraComponent>(GetTransientPackage(), NAME_None, RF_Transient);
            Niagara->bAutoActivate = false;
            Niagara->SetAutoDestroy(false);
            Niagara->bTickInEditor = true;
            Niagara->SetForceSolo(true);
            Niagara->SetAllowScalability(false);
            Niagara->SetAsset(NiagaraSystem);
            Component = Niagara;
            Scene->AddComponent(Niagara, FTransform::Identity);
            Niagara->Activate(true);
            Status = TEXT("Cooked Niagara runtime preview using compiled system data. Gameplay actors, bones, user parameters, and other game-only context are not supplied.");
        }
        else if (Cast<UNiagaraEmitter>(Asset))
        {
            // A standalone cooked emitter has no owning system's compiled dataset/bindings.
            // Making a fresh system would require its stripped graph and a recompilation.
            Status = TEXT("A standalone cooked Niagara emitter cannot be safely instantiated without its compiled Niagara system. Open the owning Niagara System to preview it. No graph editor was opened.");
        }
        else
        {
            Status = TEXT("This asset type has no runtime preview.");
        }
        UE_LOG(LogRebirthPreview, Display, TEXT("Runtime preview opened: %s (%s)"), *GetPathNameSafe(Asset), *Status);
        Focus();
    }

    // FPreviewScene owns and GC-references registered components and their asset references.
    // It outlives the base viewport client through that client's shared scene reference below.
    TSharedPtr<FPreviewScene> Scene;
    TSharedPtr<FRuntimePreviewClient> PreviewClient;
    UPrimitiveComponent* Component = nullptr;
    UParticleSystemComponent* Cascade = nullptr;
    UNiagaraComponent* Niagara = nullptr;
    TStrongObjectPtr<UMaterialInterface> PendingMaterialAsset;
    TStrongObjectPtr<UMaterialInterface> EditedMaterialSource;
    FDelegateHandle MaterialPropertyHandle;
    TWeakPtr<FActiveTimerHandle> MaterialShaderRetryTimer;
    double MaterialShaderRetryDeadline = 0.0;
    bool bMaterialShaderRetryPending = false;
    TStrongObjectPtr<USkeletalMesh> PendingSkeletalAsset;
    TWeakPtr<FActiveTimerHandle> SkeletalShaderRetryTimer;
    int32 SkeletalShaderRetryCount = 0;
    bool bSkeletalShaderRetryPending = false;
    bool bWaitingForRecoveredCompilation = false;
    double RecoveredShaderWaitStartedSeconds = 0.0;
    double NextRecoveredShaderCheckSeconds = 0.0;
    FString Status;
    FString OwnedBonamikProbeAssetPath;
    FString OwnedMaterialProbeAssetPath;
    FString AnimationFocusBefore,AnimationFocusAfter;
    FString OwnedAnimationFocusMode=TEXT("full");
    bool bAnimationFocusedEvaluatedPose=false;
    TStrongObjectPtr<UAnimSequence> AnimationAsset;
    TStrongObjectPtr<USkeletalMesh> AnimationReceivingMesh;
    bool bAnimationWantsPlay=true;
    bool bAnimationRootAlignmentEnabled=true;
};

#include "RebirthBonamikOwnedViewportProbe.inl"
#include "RebirthAnimationOwnedViewportProbe.inl"
#include "RebirthMaterialOwnedViewportProbe.inl"

class FRuntimePreviewToolkit final : public FAssetEditorToolkit, public FEditorUndoClient
{
public:
    void Initialize(UObject* Asset)
    {
        PreviewOpenAssetPath = GetPathNameSafe(Asset);
        UMaterialInstanceConstant* Instance = Cast<UMaterialInstanceConstant>(Asset);
        const bool bEditableInstance = Instance && !IsCooked(Instance);
        if (bEditableInstance)
        {
            Overrides.Reset(NewObject<URebirthMaterialInstanceOverrides>(GetTransientPackage(), NAME_None, RF_Transactional));
            if (Overrides->InitializeFromInstance(Instance))
            {
                FDetailsViewArgs Args;
                Args.bAllowSearch = true;
                Args.bHideSelectionTip = true;
                Args.NameAreaSettings = FDetailsViewArgs::HideNameArea;
                Details = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor")).CreateDetailView(Args);
                Details->SetObject(Overrides.Get());
                Details->OnFinishedChangingProperties().AddSP(this, &FRuntimePreviewToolkit::OnMaterialPropertiesChanged);
                if (GEditor) { GEditor->RegisterForUndo(this); }
            }
            else
            {
                InstanceStatus = FString::Printf(TEXT("Parameter editing unavailable: %s"), *Overrides->LastError);
            }
        }
        const bool bRuntimeType = Asset && (Asset->IsA<UMaterialInterface>() || Asset->IsA<UAnimSequence>() || Asset->IsA<USkeletalMesh>() || Asset->IsA<UParticleSystem>() || Asset->IsA<UNiagaraSystem>() || Asset->IsA<UNiagaraEmitter>());
        if (bRuntimeType)
        {
            Viewport = SNew(SRuntimePreviewViewport).Asset(Asset);
        }
        else
        {
            Inspection = URebirthMaterialDiagnosticsLibrary::GetAssetDiagnostics(Asset);
        }
        const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("RebirthRuntimePreview_v2")
            ->AddArea(FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
                ->Split(FTabManager::NewStack()->AddTab(PreviewTabId, ETabState::OpenedTab)->SetHideTabWell(true)));
        UE_LOG(LogRebirthPreview, Display, TEXT("PreviewOpenStage asset=%s stage=init_asset_editor_begin"), *PreviewOpenAssetPath);
        InitAssetEditor(EToolkitMode::Standalone, nullptr, FName(TEXT("RebirthRuntimePreviewApp")), Layout, bEditableInstance, bEditableInstance, Asset);
        UE_LOG(LogRebirthPreview, Display, TEXT("PreviewOpenStage asset=%s stage=init_asset_editor_end"), *PreviewOpenAssetPath);
    }

    virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& Manager) override
    {
        FAssetEditorToolkit::RegisterTabSpawners(Manager);
        Manager->RegisterTabSpawner(PreviewTabId, FOnSpawnTab::CreateSP(this, &FRuntimePreviewToolkit::SpawnPreviewTab))
            .SetDisplayName(FText::FromString(TEXT("Runtime Preview")));
    }

    virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& Manager) override
    {
        Manager->UnregisterTabSpawner(PreviewTabId);
        FAssetEditorToolkit::UnregisterTabSpawners(Manager);
    }

    virtual FName GetToolkitFName() const override { return FName(TEXT("RebirthRuntimePreview")); }
    virtual FText GetBaseToolkitName() const override { return FText::FromString(Details.IsValid() ? TEXT("Rebirth Material Instance") : Viewport.IsValid() ? TEXT("Rebirth Runtime Preview") : TEXT("Cooked Asset Inspector")); }
    virtual FString GetWorldCentricTabPrefix() const override { return TEXT("Runtime Preview "); }
    virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor(0.15f, 0.6f, 0.8f); }
    virtual void PostUndo(bool bSuccess) override { if (bSuccess) { RefreshMaterial(); } }
    virtual void PostRedo(bool bSuccess) override { if (bSuccess) { RefreshMaterial(); } }

private:
    void OnMaterialPropertiesChanged(const FPropertyChangedEvent&) { RefreshMaterial(); }
    void RefreshMaterial()
    {
        if (Overrides.IsValid() && Viewport.IsValid())
        {
            Overrides->RefreshFromSource();
            Viewport->RefreshEditedMaterial(Overrides->GetSource());
            if (Details.IsValid()) { Details->ForceRefresh(); }
        }
    }
    FText GetInstanceStatus() const
    {
        if (!InstanceStatus.IsEmpty()) { return FText::FromString(InstanceStatus); }
        if (Overrides.IsValid() && !Overrides->LastError.IsEmpty()) { return FText::FromString(Overrides->LastError); }
        return FText::FromString(TEXT("Enable Override to edit a scalar, vector, or texture. Save writes this instance; its parent stays intact."));
    }

    TSharedRef<SDockTab> SpawnPreviewTab(const FSpawnTabArgs&)
    {
        if (!Viewport.IsValid())
        {
            return SNew(SDockTab)
                [ SNew(SVerticalBox)
                    + SVerticalBox::Slot().AutoHeight().Padding(10.0f)
                    [ SNew(STextBlock).AutoWrapText(true).Text(FText::FromString(TEXT("Read-only cooked asset inspection. Native graph editors, Blueprint compilation, gameplay construction and asset-specific Details customizations are not started. Reference paths and container counts are shown without following references."))) ]
                    + SVerticalBox::Slot().FillHeight(1.0f).Padding(10.0f)
                    [ SNew(SScrollBox)
                        + SScrollBox::Slot()
                        [ SNew(STextBlock).AutoWrapText(true).Text(FText::FromString(Inspection)) ]
                    ]
                ];
        }
        UE_LOG(LogRebirthPreview, Display, TEXT("PreviewOpenStage asset=%s stage=receiver_picker_begin"), *PreviewOpenAssetPath);
        // The receiving picker selects existing assets. Do not construct every
        // unrelated UFactory CDO merely to offer creation entries in this picker.
        TSharedRef<SObjectPropertyEntryBox> ReceiverPicker = SNew(SObjectPropertyEntryBox)
            .AllowedClass(USkeletalMesh::StaticClass()).AllowClear(true)
            .NewAssetFactories(TOptional<TArray<UFactory*>>(TArray<UFactory*>()))
            .ObjectPath(Viewport.ToSharedRef(), &SRuntimePreviewViewport::GetAnimationReceiverPath)
            .OnObjectChanged(Viewport.ToSharedRef(), &SRuntimePreviewViewport::SetAnimationReceiverAsset);
        UE_LOG(LogRebirthPreview, Display, TEXT("PreviewOpenStage asset=%s stage=receiver_picker_end"), *PreviewOpenAssetPath);
        return SNew(SDockTab)
            [ SNew(SVerticalBox)
                + SVerticalBox::Slot().AutoHeight().Padding(8.0f)
                [ SNew(SHorizontalBox)
                    + SHorizontalBox::Slot().AutoWidth().Padding(2.0f)
                    [ SNew(SButton).Text(Viewport.ToSharedRef(), &SRuntimePreviewViewport::PlaybackLabel).OnClicked(Viewport.ToSharedRef(), &SRuntimePreviewViewport::TogglePlayback) ]
                    + SHorizontalBox::Slot().AutoWidth().Padding(2.0f)
                    [ SNew(SButton).Text(FText::FromString(TEXT("Restart"))).OnClicked(Viewport.ToSharedRef(), &SRuntimePreviewViewport::Restart) ]
                    + SHorizontalBox::Slot().AutoWidth().Padding(2.0f)
                    [ SNew(SButton).Text(FText::FromString(TEXT("Focus"))).OnClicked(Viewport.ToSharedRef(), &SRuntimePreviewViewport::Focus) ]
                    + SHorizontalBox::Slot().AutoWidth().Padding(2.0f)
                    [ SNew(SButton).Text(Viewport.ToSharedRef(),&SRuntimePreviewViewport::AnimationRootAlignmentLabel)
                        .Visibility(Viewport.ToSharedRef(),&SRuntimePreviewViewport::AnimationVisibility)
                        .ToolTipText(FText::FromString(TEXT("Preview only: align the original clip's first-frame root orientation with the receiving mesh reference root. The component rotation stays constant; animation poses and assets are unchanged. Turn off to inspect the original orientation.")))
                        .OnClicked(Viewport.ToSharedRef(),&SRuntimePreviewViewport::ToggleAnimationRootAlignment) ]
                    + SHorizontalBox::Slot().AutoWidth().Padding(2.0f)
                    [ SNew(SButton)
                        .Text(Viewport.ToSharedRef(), &SRuntimePreviewViewport::BonamikLabel)
                        .Visibility(Viewport.ToSharedRef(), &SRuntimePreviewViewport::BonamikVisibility)
                        .ToolTipText(FText::FromString(TEXT("Toggle the custom Bonamik-data preview. Pause stops simulation; Restart resets it. Original assets are not changed.")))
                        .OnClicked(Viewport.ToSharedRef(), &SRuntimePreviewViewport::ToggleBonamik) ]
                ]
                + SVerticalBox::Slot().AutoHeight().Padding(8.0f)
                [ SNew(SHorizontalBox).Visibility(Viewport.ToSharedRef(),&SRuntimePreviewViewport::AnimationVisibility)
                    + SHorizontalBox::Slot().AutoWidth().Padding(4.0f) [ SNew(STextBlock).Text(FText::FromString(TEXT("Receiving mesh"))) ]
                    + SHorizontalBox::Slot().FillWidth(1.0f).Padding(4.0f)
                    [ ReceiverPicker ]
                    + SHorizontalBox::Slot().FillWidth(1.0f).Padding(4.0f)
                    [ SNew(SSlider).IsEnabled(Viewport.ToSharedRef(),&SRuntimePreviewViewport::IsAnimationReady)
                        .Value(Viewport.ToSharedRef(),&SRuntimePreviewViewport::GetAnimationNormalizedPosition)
                        .OnValueChanged(Viewport.ToSharedRef(),&SRuntimePreviewViewport::SetAnimationNormalizedPosition) ]
                    + SHorizontalBox::Slot().AutoWidth().Padding(4.0f)
                    [ SNew(STextBlock).Text(Viewport.ToSharedRef(),&SRuntimePreviewViewport::GetAnimationPositionLabel) ]
                ]
                + SVerticalBox::Slot().AutoHeight().Padding(8.0f)
                [ SNew(STextBlock).AutoWrapText(true).Visibility(Overrides.IsValid() ? EVisibility::Visible : EVisibility::Collapsed).Text(this, &FRuntimePreviewToolkit::GetInstanceStatus) ]
                + SVerticalBox::Slot().FillHeight(1.0f)
                [ SNew(SSplitter)
                    + SSplitter::Slot().Value(0.55f) [ Viewport.ToSharedRef() ]
                    + SSplitter::Slot().Value(0.45f)
                    [ Details.IsValid() ? StaticCastSharedRef<SWidget>(Details.ToSharedRef()) : StaticCastSharedRef<SWidget>(SNew(STextBlock).Visibility(EVisibility::Collapsed)) ]
                ]
                + SVerticalBox::Slot().AutoHeight().Padding(8.0f)
                [ SNew(STextBlock).AutoWrapText(true).Text(Viewport.ToSharedRef(), &SRuntimePreviewViewport::GetStatus) ]
            ];
    }
    FString PreviewOpenAssetPath;
    TSharedPtr<SRuntimePreviewViewport> Viewport;
    TStrongObjectPtr<URebirthMaterialInstanceOverrides> Overrides;
    TSharedPtr<IDetailsView> Details;
    FString InstanceStatus;
    FString Inspection;
};

static void OpenPreview(UObject* Object)
{
    if (Object && !IsRunningCommandlet())
    {
        MakeShared<FRuntimePreviewToolkit>()->Initialize(Object);
    }
}

static void CreateEditableInstances(const TArray<TWeakObjectPtr<UMaterialInterface>>& Parents)
{
    IAssetTools& Tools = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools")).Get();
    for (const TWeakObjectPtr<UMaterialInterface>& Parent : Parents)
    {
        if (!Parent.IsValid()) { continue; }
        FString PackageName, Name;
        Tools.CreateUniqueAssetName(Parent->GetOutermost()->GetName(), TEXT("_Inst"), PackageName, Name);
        UMaterialInstanceConstantFactoryNew* Factory = NewObject<UMaterialInstanceConstantFactoryNew>();
        Factory->InitialParent = Parent.Get();
        if (UObject* Created = Tools.CreateAssetWithDialog(Name, FPackageName::GetLongPackagePath(PackageName), UMaterialInstanceConstant::StaticClass(), Factory))
        {
            // The new instance is editable: open it in Unreal's own Material Instance Editor.
            if (GEditor) { GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(Created); }
        }
    }
}

static TArray<TWeakObjectPtr<UMaterialInterface>> GetProtectedMaterialParents(const TArray<UObject*>& Objects)
{
    TArray<TWeakObjectPtr<UMaterialInterface>> Parents;
    for (UObject* Object : Objects)
    {
        if (NeedsProtectedEditor(Object))
        {
            if (UMaterialInterface* Material = Cast<UMaterialInterface>(Object)) { Parents.Add(Material); }
        }
    }
    return Parents;
}

// Cooked animation, skeleton and mesh assets still use their complete native
// Persona editors. Material and graph-only cooked assets retain protected opening.
static bool UsesNativePersona(UObject* Object)
{
    return Object && (Object->IsA<UAnimationAsset>() || Object->IsA<USkeleton>() || Object->IsA<USkeletalMesh>());
}

// A material instance saved in this project (not cooked) opens in Unreal's own Material Instance Editor, even
// when its parent chain is cooked game material. "Open Rebirth Runtime Preview" stays on its context menu.
static bool IsEditableMaterialInstance(UObject* Object)
{
    return Object && Object->IsA<UMaterialInstanceConstant>() && !IsCooked(Object);
}

static TAutoConsoleVariable<int32> CVarCookedInstancesPreviewWindow(
    TEXT("Rebirth.CookedMaterialInstances.PreviewWindow"),
    0,
    TEXT("0 (default): material instances, cooked ones included, open in Unreal's own Material Instance Editor (the cooked base ")
    TEXT("material's stripped editor data is padded first). 1: cooked material instances open in the read-only Rebirth Runtime ")
    TEXT("Preview window instead. \"Open Rebirth Runtime Preview\" stays on their right-click menu either way."),
    ECVF_Default);

// Material instances, cooked ones included, open in Unreal's own Material Instance Editor unless the preview window is asked
// for, or their render state can't be drawn (an unknown blend mode, shading model or domain: the editor's preview would
// assert in the renderer).
static bool OpensInNativeInstanceEditor(UObject* Object)
{
    UMaterialInstance* Instance = Cast<UMaterialInstance>(Object);
    if (Instance == nullptr || CVarCookedInstancesPreviewWindow.GetValueOnGameThread() != 0)
    {
        return false;
    }
    const RebirthMaterialPreviewSafety::FResult Result = RebirthMaterialPreviewSafety::Evaluate(Instance);
    return Result.bParentChainValid && !Result.bHasUnsupportedRenderState;
}

static bool UsesProtectedDefaultEditor(UObject* Object)
{
    if (IsEditableMaterialInstance(Object)) { return false; }
    if (OpensInNativeInstanceEditor(Object)) { return false; }
    return NeedsProtectedEditor(Object) && !UsesNativePersona(Object);
}

static TArray<TWeakObjectPtr<UObject>> GetRuntimePreviewObjects(const TArray<UObject*>& Objects)
{
    TArray<TWeakObjectPtr<UObject>> Result;
    for (UObject* Object : Objects)
    {
        if (Object && NeedsProtectedEditor(Object)) { Result.Add(Object); }
    }
    return Result;
}

static FUIAction RuntimePreviewAction(const TArray<TWeakObjectPtr<UObject>>& Objects)
{
    return FUIAction(FExecuteAction::CreateLambda([Objects]()
    {
        for (const TWeakObjectPtr<UObject>& Object : Objects)
        {
            if (Object.IsValid()) { OpenPreview(Object.Get()); }
        }
    }));
}

static FString MakeDataObjectEditableTooltip()
{
    return TEXT("Turn this cooked data object (a copy of the game's file) into a normal editable asset at the same path, with all of its rows. ")
        TEXT("It opens in the Data Object table editor, and Package Project ships it in the game's format. The cooked files are moved to Saved/RebirthDataObjectBackups/ first.");
}

static FString MakeDataAssetEditableTooltip()
{
    return TEXT("Turn this cooked data asset (a copy of the game's file) into a normal editable asset at the same path, with all of its properties. ")
        TEXT("References to game assets that are not in this project are kept. Package Project ships it; duplicate it to make new ones (for example a new character's CharaSpec). ")
        TEXT("The cooked files are moved to Saved/RebirthDataAssetBackups/ first.");
}

static FString MakeEditableTooltip()
{
    return TEXT("Turn this cooked material instance into a normal editable Material Instance at the same path (same parent, parameters, static switches and overrides). ")
        TEXT("The cooked files are moved to Saved/RebirthCookedOriginals/ first.");
}

// Decorate original actions while preserving the complete native Persona route.
class FPreviewAssetActions final : public FAssetTypeActions_Base
{
public:
    explicit FPreviewAssetActions(TSharedRef<IAssetTypeActions> InOriginal) : Original(InOriginal)
    {
        SetSupported(Original->IsSupported());
    }

    TSharedRef<IAssetTypeActions> GetOriginal() const { return Original; }
    virtual FText GetName() const override { return Original->GetName(); }
    virtual UClass* GetSupportedClass() const override { return Original->GetSupportedClass(); }
    virtual FColor GetTypeColor() const override { return Original->GetTypeColor(); }
    virtual uint32 GetCategories() override { return Original->GetCategories(); }
    virtual FString GetObjectDisplayName(UObject* Object) const override { return Original->GetObjectDisplayName(Object); }
    virtual const TArray<FText>& GetSubMenus() const override { return Original->GetSubMenus(); }
    virtual bool CanFilter() override { return Original->CanFilter(); }
    virtual bool CanLocalize() const override { return Original->CanLocalize(); }
    virtual bool CanMerge() const override { return Original->CanMerge(); }
    virtual void Merge(UObject* Object) override { Original->Merge(Object); }
    virtual void Merge(UObject* Base, UObject* Remote, UObject* Local, const FOnMergeResolved& Callback) override { Original->Merge(Base, Remote, Local, Callback); }
    virtual bool ShouldForceWorldCentric() override { return Original->ShouldForceWorldCentric(); }
    virtual void PerformAssetDiff(UObject* Old, UObject* New, const FRevisionInfo& OldRevision, const FRevisionInfo& NewRevision) const override { Original->PerformAssetDiff(Old, New, OldRevision, NewRevision); }
    virtual UThumbnailInfo* GetThumbnailInfo(UObject* Object) const override { return Original->GetThumbnailInfo(Object); }
    virtual EThumbnailPrimType GetDefaultThumbnailPrimitiveType(UObject* Object) const override { return Original->GetDefaultThumbnailPrimitiveType(Object); }
    virtual TSharedPtr<SWidget> GetThumbnailOverlay(const FAssetData& Data) const override { return Original->GetThumbnailOverlay(Data); }
    virtual FText GetAssetDescription(const FAssetData& Data) const override { return Original->GetAssetDescription(Data); }
    virtual bool IsImportedAsset() const override { return Original->IsImportedAsset(); }
    virtual void GetResolvedSourceFilePaths(const TArray<UObject*>& Objects, TArray<FString>& Paths) const override { Original->GetResolvedSourceFilePaths(Objects, Paths); }
    virtual void GetSourceFileLabels(const TArray<UObject*>& Objects, TArray<FString>& Labels) const override { Original->GetSourceFileLabels(Objects, Labels); }
    virtual void BuildBackendFilter(FARFilter& Filter) override { Original->BuildBackendFilter(Filter); }
    virtual FText GetDisplayNameFromAssetData(const FAssetData& Data) const override { return Original->GetDisplayNameFromAssetData(Data); }

    virtual bool HasActions(const TArray<UObject*>& Objects) const override
    {
        TArray<UObject*> Editable;
        for (UObject* Object : Objects) { if (!UsesProtectedDefaultEditor(Object)) { Editable.Add(Object); } }
        return GetRuntimePreviewObjects(Objects).Num() > 0 || GetProtectedMaterialParents(Objects).Num() > 0 || (Editable.Num() > 0 && Original->HasActions(Editable))
            || RebirthDataObjectEditing::GetConvertible(Objects).Num() > 0 || RebirthAssetConversion::GetConvertible(Objects).Num() > 0;
    }
    virtual void GetActions(const TArray<UObject*>& Objects, FMenuBuilder& Menu) override
    {
        TArray<UObject*> Editable;
        for (UObject* Object : Objects) { if (!UsesProtectedDefaultEditor(Object)) { Editable.Add(Object); } }
        if (Editable.Num() > 0) { Original->GetActions(Editable, Menu); }
        const TArray<TWeakObjectPtr<UObject>> PreviewObjects = GetRuntimePreviewObjects(Objects);
        if (PreviewObjects.Num() > 0)
        {
            Menu.AddMenuEntry(FText::FromString(TEXT("Open Rebirth Runtime Preview")),
                FText::FromString(TEXT("Open the Rebirth preview alongside the native asset editor.")),
                FSlateIcon(), RuntimePreviewAction(PreviewObjects));
        }
        const TArray<TWeakObjectPtr<UMaterialInterface>> Parents = GetProtectedMaterialParents(Objects);
        if (Parents.Num() > 0)
        {
            Menu.AddMenuEntry(FText::FromString(TEXT("Create Editable Material Instance")), FText::FromString(TEXT("Create a new editable instance that keeps this material as its parent.")), FSlateIcon(),
                FUIAction(FExecuteAction::CreateLambda([Parents]() { CreateEditableInstances(Parents); })));
        }
        const TArray<TWeakObjectPtr<UMaterialInstanceConstant>> Convertible = RebirthCookedMaterialConversion::GetConvertible(Objects);
        if (Convertible.Num() > 0)
        {
            Menu.AddMenuEntry(FText::FromString(TEXT("Make Editable (convert cooked instance)")), FText::FromString(MakeEditableTooltip()), FSlateIcon(),
                FUIAction(FExecuteAction::CreateLambda([Convertible]() { RebirthCookedMaterialConversion::MakeEditableWithDialog(Convertible); })));
        }
        const TArray<TWeakObjectPtr<UEndDataObjectBase>> DataObjects = RebirthDataObjectEditing::GetConvertible(Objects);
        if (DataObjects.Num() > 0)
        {
            Menu.AddMenuEntry(FText::FromString(TEXT("Make Editable (convert cooked data object)")), FText::FromString(MakeDataObjectEditableTooltip()), FSlateIcon(),
                FUIAction(FExecuteAction::CreateLambda([DataObjects]() { RebirthDataObjectEditing::MakeEditableWithDialog(DataObjects); })));
        }
        const TArray<TWeakObjectPtr<UObject>> DataAssets = RebirthAssetConversion::GetConvertible(Objects);
        if (DataAssets.Num() > 0)
        {
            Menu.AddMenuEntry(FText::FromString(TEXT("Make Editable (convert cooked data asset)")), FText::FromString(MakeDataAssetEditableTooltip()), FSlateIcon(),
                FUIAction(FExecuteAction::CreateLambda([DataAssets]() { RebirthAssetConversion::MakeEditableWithDialog(DataAssets); })));
        }
    }
    virtual void GetActions(const TArray<UObject*>& Objects, FToolMenuSection& Section) override
    {
        TArray<UObject*> Editable;
        for (UObject* Object : Objects) { if (!UsesProtectedDefaultEditor(Object)) { Editable.Add(Object); } }
        if (Editable.Num() > 0) { Original->GetActions(Editable, Section); }
        const TArray<TWeakObjectPtr<UObject>> PreviewObjects = GetRuntimePreviewObjects(Objects);
        if (PreviewObjects.Num() > 0)
        {
            Section.AddMenuEntry(TEXT("RebirthOpenRuntimePreview"), FText::FromString(TEXT("Open Rebirth Runtime Preview")),
                FText::FromString(TEXT("Open the Rebirth preview alongside the native asset editor.")),
                FSlateIcon(), RuntimePreviewAction(PreviewObjects));
        }
        const TArray<TWeakObjectPtr<UMaterialInterface>> Parents = GetProtectedMaterialParents(Objects);
        if (Parents.Num() > 0)
        {
            Section.AddMenuEntry(TEXT("RebirthCreateEditableMI"), FText::FromString(TEXT("Create Editable Material Instance")), FText::FromString(TEXT("Create a new editable instance that keeps this material as its parent.")), FSlateIcon(),
                FUIAction(FExecuteAction::CreateLambda([Parents]() { CreateEditableInstances(Parents); })));
        }
        const TArray<TWeakObjectPtr<UMaterialInstanceConstant>> Convertible = RebirthCookedMaterialConversion::GetConvertible(Objects);
        if (Convertible.Num() > 0)
        {
            Section.AddMenuEntry(TEXT("RebirthMakeCookedEditable"), FText::FromString(TEXT("Make Editable (convert cooked instance)")), FText::FromString(MakeEditableTooltip()), FSlateIcon(),
                FUIAction(FExecuteAction::CreateLambda([Convertible]() { RebirthCookedMaterialConversion::MakeEditableWithDialog(Convertible); })));
        }
        const TArray<TWeakObjectPtr<UEndDataObjectBase>> DataObjects = RebirthDataObjectEditing::GetConvertible(Objects);
        if (DataObjects.Num() > 0)
        {
            Section.AddMenuEntry(TEXT("RebirthMakeDataObjectEditable"), FText::FromString(TEXT("Make Editable (convert cooked data object)")), FText::FromString(MakeDataObjectEditableTooltip()), FSlateIcon(),
                FUIAction(FExecuteAction::CreateLambda([DataObjects]() { RebirthDataObjectEditing::MakeEditableWithDialog(DataObjects); })));
        }
        const TArray<TWeakObjectPtr<UObject>> DataAssets = RebirthAssetConversion::GetConvertible(Objects);
        if (DataAssets.Num() > 0)
        {
            Section.AddMenuEntry(TEXT("RebirthMakeDataAssetEditable"), FText::FromString(TEXT("Make Editable (convert cooked data asset)")), FText::FromString(MakeDataAssetEditableTooltip()), FSlateIcon(),
                FUIAction(FExecuteAction::CreateLambda([DataAssets]() { RebirthAssetConversion::MakeEditableWithDialog(DataAssets); })));
        }
    }
    virtual TArray<FAssetData> GetValidAssetsForPreviewOrEdit(TArrayView<const FAssetData> Data, bool bPreview) override
    {
        // The decorated Niagara action may filter cooked assets because its graph editor
        // cannot edit them. This window requires only the actual runtime object.
        TArray<FAssetData> EditableData;
        TArray<FAssetData> CookedData;
        for (const FAssetData& Asset : Data)
        {
            if (Asset.HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly))
            {
                CookedData.Add(Asset);
            }
            else { EditableData.Add(Asset); }
        }
        TArray<FAssetData> Result = Original->GetValidAssetsForPreviewOrEdit(EditableData, bPreview);
        for (const FAssetData& Asset : CookedData) { Result.AddUnique(Asset); }
        return Result;
    }
    virtual void OpenAssetEditor(const TArray<UObject*>& Objects, TSharedPtr<IToolkitHost> Host = nullptr) override
    {
        TArray<UObject*> Editable;
        for (UObject* Object : Objects)
        {
            // Cooked RM_Surface chains switch to the recovered in-game shading before any preview resolves them.
            RebirthRecoveredSurfaces::ApplyNow(Object);
            // A cooked data object (CharaSpec and so on) can become an editable table instead of the read-only preview.
            if (RebirthDataObjectEditing::OfferMakeEditableOnOpen(Object)) { continue; }
            // A cooked data asset (CharaSpec_<character> and so on) can become an editable asset instead of the read-only preview.
            if (RebirthAssetConversion::OfferMakeEditableOnOpen(Object)) { continue; }
            if (UsesProtectedDefaultEditor(Object)) { OpenPreview(Object); }
            else
            {
                // The Material Instance Editor reads per-parameter editor metadata from the base material; a cooked
                // base material (RM_Surface) lost it in the cook, so fill it before the editor indexes it.
                if (const UMaterialInterface* Material = Cast<UMaterialInterface>(Object)) { RebirthCookedMaterialMetadata::RepairChain(Material); }
                Editable.Add(Object);
            }
        }
        if (Editable.Num() > 0) { Original->OpenAssetEditor(Editable, Host); }
    }
    virtual bool AssetsActivatedOverride(const TArray<UObject*>& Objects, EAssetTypeActivationMethod::Type Activation) override
    {
        bool bHasCooked = false;
        for (UObject* Object : Objects)
        {
            if (UsesProtectedDefaultEditor(Object)) { bHasCooked = true; }
        }
        if (!bHasCooked) { return Original->AssetsActivatedOverride(Objects, Activation); }
        OpenAssetEditor(Objects);
        return true;
    }

private:
    TSharedRef<IAssetTypeActions> Original;
};

// Some game data types have no type action at all. A UObject fallback supplies
// protective opening for their cooked packages while retaining the engine's
// generic object editor for an editable unknown type.
class FUnknownObjectActions final : public FAssetTypeActions_Base
{
public:
    explicit FUnknownObjectActions(UClass* InClass) : SupportedClass(InClass) { check(SupportedClass); }
    virtual FText GetName() const override { return FText::FromString(TEXT("Object")); }
    virtual UClass* GetSupportedClass() const override { return SupportedClass; }
    virtual FColor GetTypeColor() const override { return FColor::Silver; }
    virtual uint32 GetCategories() override { return EAssetTypeCategories::Misc; }
    virtual bool CanFilter() override { return false; }
    virtual bool HasActions(const TArray<UObject*>& Objects) const override
    {
        return RebirthDataObjectEditing::GetConvertible(Objects).Num() > 0 || RebirthAssetConversion::GetConvertible(Objects).Num() > 0;
    }
    virtual void GetActions(const TArray<UObject*>& Objects, FMenuBuilder& Menu) override
    {
        const TArray<TWeakObjectPtr<UEndDataObjectBase>> DataObjects = RebirthDataObjectEditing::GetConvertible(Objects);
        if (DataObjects.Num() > 0)
        {
            Menu.AddMenuEntry(FText::FromString(TEXT("Make Editable (convert cooked data object)")), FText::FromString(MakeDataObjectEditableTooltip()), FSlateIcon(),
                FUIAction(FExecuteAction::CreateLambda([DataObjects]() { RebirthDataObjectEditing::MakeEditableWithDialog(DataObjects); })));
        }
        const TArray<TWeakObjectPtr<UObject>> DataAssets = RebirthAssetConversion::GetConvertible(Objects);
        if (DataAssets.Num() > 0)
        {
            Menu.AddMenuEntry(FText::FromString(TEXT("Make Editable (convert cooked data asset)")), FText::FromString(MakeDataAssetEditableTooltip()), FSlateIcon(),
                FUIAction(FExecuteAction::CreateLambda([DataAssets]() { RebirthAssetConversion::MakeEditableWithDialog(DataAssets); })));
        }
    }
    virtual void GetActions(const TArray<UObject*>& Objects, FToolMenuSection& Section) override
    {
        const TArray<TWeakObjectPtr<UEndDataObjectBase>> DataObjects = RebirthDataObjectEditing::GetConvertible(Objects);
        if (DataObjects.Num() > 0)
        {
            Section.AddMenuEntry(TEXT("RebirthMakeDataObjectEditable"), FText::FromString(TEXT("Make Editable (convert cooked data object)")), FText::FromString(MakeDataObjectEditableTooltip()), FSlateIcon(),
                FUIAction(FExecuteAction::CreateLambda([DataObjects]() { RebirthDataObjectEditing::MakeEditableWithDialog(DataObjects); })));
        }
        const TArray<TWeakObjectPtr<UObject>> DataAssets = RebirthAssetConversion::GetConvertible(Objects);
        if (DataAssets.Num() > 0)
        {
            Section.AddMenuEntry(TEXT("RebirthMakeDataAssetEditable"), FText::FromString(TEXT("Make Editable (convert cooked data asset)")), FText::FromString(MakeDataAssetEditableTooltip()), FSlateIcon(),
                FUIAction(FExecuteAction::CreateLambda([DataAssets]() { RebirthAssetConversion::MakeEditableWithDialog(DataAssets); })));
        }
    }
    virtual void OpenAssetEditor(const TArray<UObject*>& Objects, TSharedPtr<IToolkitHost> Host = nullptr) override
    {
        TArray<UObject*> Editable;
        for (UObject* Object : Objects)
        {
            if (RebirthDataObjectEditing::OfferMakeEditableOnOpen(Object)) { continue; }
            if (RebirthAssetConversion::OfferMakeEditableOnOpen(Object)) { continue; }
            if (IsCooked(Object)) { OpenPreview(Object); }
            else { Editable.Add(Object); }
        }
        if (Editable.Num() > 0) { FAssetTypeActions_Base::OpenAssetEditor(Editable, Host); }
    }
private:
    UClass* SupportedClass;
};
}

class FRebirthMaterialPreviewModule final : public IModuleInterface
{
public:
    // Preview windows own C++ viewport callbacks until closed. Do not unload their
    // module through dynamic hot-reload while those windows may still be alive.
    virtual bool SupportsDynamicReloading() override { return false; }

    virtual void StartupModule() override
    {
        // Commandlets (cook, Alpakit) only: retail shader map layout mismatches must not fail the commandlet,
        // and already-cooked game textures are left out of the cook instead of stalling it.
        RebirthCookLogFilter::Install();
        RebirthCookedTextureSkip::Install();
        // Every process: cooked data objects load with their rows, editable ones save their rows, cooking writes the game's format
        // (and adds edited data objects under /Game to the cook).
        RebirthDataObjects::Install();
        // Every process: editable assets keep their references to game assets that are not in this project (also when cooking).
        RebirthGameReferences::Install();
        RebirthNiagaraVfx1LoadAdapter::Startup();
        if (IsRunningCommandlet()) { return; }
        PreExitHandle = FCoreDelegates::OnPreExit.AddRaw(this, &FRebirthMaterialPreviewModule::OnPreExit);
        RebirthSkeletonCompatibilityEditor::Startup();
        RebirthPersonaOwnedProbe::Register();
        RebirthMaterialOwnedProbe::Register();
        RebirthPersonaPreviewSupport::Register();
        RebirthCookedMaterialMetadata::Startup();
        // In-game shading for cooked RM_Surface materials (editor only, in memory only) and cooked->editable conversion.
        RebirthRecoveredSurfaces::Startup();
        RebirthCookedMaterialConversion::Register();
        // Make Editable / Import Data Object from Game for CharaSpec and the other data objects.
        RebirthDataObjectEditing::Register();
        // Saving a CharaSpec table checks its changed rows for references the game cannot resolve.
        RebirthCharaSpecCheck::Register();
        // Make Editable for cooked data assets; the Game Blueprints window and child blueprints.
        RebirthAssetConversion::Register();
        RebirthBlueprintTools::Register();
        check(RebirthPreview::RegisterMaterialCompanions());
        InstallMaterialThumbnailGuards();
        // Ensure Niagara's original actions exist before decorating them.
        FModuleManager::LoadModuleChecked<IModuleInterface>(TEXT("NiagaraEditor"));
        IAssetTools& Tools = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools")).Get();
        // A UObject-wide fallback also appears in specialized factory lists.
        // Keep this fallback scoped to Rebirth data objects so native factories
        // can rely on their concrete action types.
        if (UClass* DataClass = FindObject<UClass>(nullptr, TEXT("/Script/EndDataObject.EndDataObjectBase")))
        {
            Fallback = MakeShared<RebirthPreview::FUnknownObjectActions>(DataClass);
            Tools.RegisterAssetTypeActions(Fallback.ToSharedRef());
        }
        // The game's data types that have no asset actions of their own (anim sets, asset packs).
        static const TCHAR* const PlainDataClasses[] = { TEXT("/Script/EndGame.EndAnimSet"), TEXT("/Script/EndGame.EndAssetPack") };
        for (const TCHAR* ClassPath : PlainDataClasses)
        {
            if (UClass* PlainClass = FindObject<UClass>(nullptr, ClassPath))
            {
                TSharedRef<RebirthPreview::FUnknownObjectActions> Action = MakeShared<RebirthPreview::FUnknownObjectActions>(PlainClass);
                Tools.RegisterAssetTypeActions(Action);
                PlainDataFallbacks.Add(Action);
            }
        }
        DecorateRegisteredActions();
        ModulesChangedHandle = FModuleManager::Get().OnModulesChanged().AddRaw(this, &FRebirthMaterialPreviewModule::OnModulesChanged);
        if (FParse::Param(FCommandLine::Get(), TEXT("RebirthBonamikOwnedPreviewProbe")))
        {
            BonamikProbeCommand = MakeUnique<FAutoConsoleCommand>(TEXT("Rebirth.BonamikProbe"),
                TEXT("Owned test process only: snapshot|play|pause|on|off|restart|step <seconds>. Writes Saved/BonamikOwnedProbe/LatestState.json."),
                FConsoleCommandWithArgsDelegate::CreateStatic(&RebirthPreview::RunBonamikOwnedProbe));
        }
        if (FParse::Param(FCommandLine::Get(),TEXT("RebirthAnimationOwnedPreviewProbe")))
        {
            AnimationProbeCommand=MakeUnique<FAutoConsoleCommand>(TEXT("Rebirth.AnimationProbe"),
                TEXT("Owned process only: snapshot|receiver <loaded mesh>|play|pause|restart|seek <seconds>|step <seconds>|capture <label>. Writes Saved/AnimationOwnedProbe/LatestState.json."),
                FConsoleCommandWithArgsDelegate::CreateStatic(&RebirthPreview::RunAnimationOwnedProbe));
        }
        if (FParse::Param(FCommandLine::Get(), TEXT("RebirthMaterialOwnedProbe")))
        {
            MaterialProbeCommand = MakeUnique<FAutoConsoleCommand>(TEXT("Rebirth.MaterialProbe"),
                TEXT("Owned process only: snapshot|capture <label>. Writes Saved/MaterialOwnedProbe/LatestViewport.json."),
                FConsoleCommandWithArgsDelegate::CreateStatic(&RebirthPreview::RunMaterialOwnedProbe));
        }
        PreviewCommand = MakeUnique<FAutoConsoleCommand>(TEXT("Rebirth.PreviewCooked"),
            TEXT("Preview an already loaded cooked asset: Rebirth.PreviewCooked /Game/Path/Asset.Asset"),
            FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Arguments)
            {
                if (Arguments.Num() != 1) { UE_LOG(LogRebirthPreview, Warning, TEXT("Usage: Rebirth.PreviewCooked /Game/Path/Asset.Asset")); return; }
                UObject* Object = FindObject<UObject>(nullptr, *Arguments[0]);
                if (!Object) { UE_LOG(LogRebirthPreview, Warning, TEXT("Asset must already be loaded: %s"), *Arguments[0]); return; }
                if (!RebirthPreview::IsCooked(Object)) { UE_LOG(LogRebirthPreview, Warning, TEXT("Asset is editable; open its normal editor: %s"), *Arguments[0]); return; }
                RebirthPreview::OpenPreview(Object);
            }));
        UE_LOG(LogRebirthPreview, Display, TEXT("Cooked runtime preview registered for %d asset types."), Actions.Num());
    }

    virtual void ShutdownModule() override
    {
        RebirthCookLogFilter::Uninstall();
        RebirthCharaSpecCheck::Unregister();
        RebirthDataObjectEditing::Unregister();
        RebirthAssetConversion::Unregister();
        RebirthBlueprintTools::Unregister();
        RebirthGameReferences::Uninstall();
        RebirthDataObjects::Uninstall();
        RebirthCookedTextureSkip::Uninstall();
        RebirthCookedMaterialConversion::Unregister();
        RebirthRecoveredSurfaces::Shutdown();
        RebirthCookedMaterialMetadata::Shutdown();
        RebirthNiagaraVfx1LoadAdapter::Shutdown();
        RebirthPersonaOwnedProbe::Unregister();
        RebirthMaterialOwnedProbe::Unregister();
        RebirthPersonaPreviewSupport::Unregister();
        // Compatibility roots are normally released by OnPreExit before UObject purge.
        if (UObjectInitialized() && !IsEngineExitRequested()) { RebirthSkeletonCompatibilityEditor::Shutdown(); }
        FCoreDelegates::OnPreExit.Remove(PreExitHandle);
        FModuleManager::Get().OnModulesChanged().Remove(ModulesChangedHandle);
        BonamikProbeCommand.Reset();
        AnimationProbeCommand.Reset();
        MaterialProbeCommand.Reset();
        PreviewCommand.Reset();
        // Engine-loop module shutdown follows StaticExit's UObject purge. Only a
        // live, non-exit unload may access thumbnail managers or asset actions.
        if (!IsEngineExitRequested() && UObjectInitialized())
        {
            RestoreMaterialThumbnailRenderers();
            if (FAssetToolsModule* Module = FModuleManager::GetModulePtr<FAssetToolsModule>(TEXT("AssetTools")))
            {
                for (const TSharedRef<RebirthPreview::FPreviewAssetActions>& Action : Actions)
                {
                    Module->Get().UnregisterAssetTypeActions(Action);
                    Module->Get().RegisterAssetTypeActions(Action->GetOriginal());
                }
                if (Fallback.IsValid()) { Module->Get().UnregisterAssetTypeActions(Fallback.ToSharedRef()); }
                for (const TSharedRef<RebirthPreview::FUnknownObjectActions>& Action : PlainDataFallbacks) { Module->Get().UnregisterAssetTypeActions(Action); }
            }
        }
        OriginalMaterialThumbnailClass.Reset();
        OriginalInstanceThumbnailClass.Reset();
        OriginalSkeletalThumbnailClass.Reset();
        Actions.Empty();
        Decorators.Empty();
        Fallback.Reset();
        PlainDataFallbacks.Empty();
    }

private:
    void OnPreExit()
    {
        RebirthSkeletonCompatibilityEditor::Shutdown();
        // Menus are UObjects; release them while UObjects still exist.
        RebirthDataObjectEditing::Unregister();
        RebirthAssetConversion::Unregister();
        RebirthBlueprintTools::Unregister();
        // Releases the transient recovered masters while UObjects still exist.
        RebirthCookedMaterialConversion::Unregister();
        RebirthRecoveredSurfaces::Shutdown();
        // AppPreExit broadcasts this before OnExit invokes StaticExit. Renderer
        // restoration constructs UObjects and must finish before that purge.
        FModuleManager::Get().OnModulesChanged().Remove(ModulesChangedHandle);
        RestoreMaterialThumbnailRenderers();
    }

    void InstallMaterialThumbnailGuards()
    {
        UThumbnailManager& Manager = UThumbnailManager::Get();
        // Capture both classes before removing entries: unregistering invalidates rendering-info pointers.
        FThumbnailRenderingInfo* MaterialInfo = Manager.GetRenderingInfo(GetMutableDefault<UMaterial>());
        OriginalMaterialThumbnailClass.Reset(MaterialInfo && MaterialInfo->Renderer ? MaterialInfo->Renderer->GetClass() : nullptr);
        FThumbnailRenderingInfo* InstanceInfo = Manager.GetRenderingInfo(GetMutableDefault<UMaterialInstanceConstant>());
        OriginalInstanceThumbnailClass.Reset(InstanceInfo && InstanceInfo->Renderer ? InstanceInfo->Renderer->GetClass() : nullptr);
        FThumbnailRenderingInfo* SkeletalInfo = Manager.GetRenderingInfo(GetMutableDefault<USkeletalMesh>());
        OriginalSkeletalThumbnailClass.Reset(SkeletalInfo && SkeletalInfo->Renderer ? SkeletalInfo->Renderer->GetClass() : nullptr);
        InstallThumbnailGuard(Manager, UMaterial::StaticClass(), OriginalMaterialThumbnailClass.Get());
        InstallThumbnailGuard(Manager, UMaterialInterface::StaticClass(), OriginalInstanceThumbnailClass.Get());
        if (OriginalSkeletalThumbnailClass.IsValid() && GetMutableDefault<URebirthSafeSkeletalMeshThumbnailRenderer>()->SetDelegateRendererClass(OriginalSkeletalThumbnailClass.Get()))
        {
            Manager.UnregisterCustomRenderer(USkeletalMesh::StaticClass());
            Manager.RegisterCustomRenderer(USkeletalMesh::StaticClass(), URebirthSafeSkeletalMeshThumbnailRenderer::StaticClass());
        }
    }

    static void InstallThumbnailGuard(UThumbnailManager& Manager, UClass* AssetClass, UClass* OriginalClass)
    {
        if (!OriginalClass || !GetMutableDefault<URebirthSafeMaterialThumbnailRenderer>()->SetDelegateRendererClass(OriginalClass)) { return; }
        Manager.UnregisterCustomRenderer(AssetClass);
        Manager.RegisterCustomRenderer(AssetClass, URebirthSafeMaterialThumbnailRenderer::StaticClass());
    }

    void RestoreMaterialThumbnailRenderers()
    {
        if (bThumbnailGuardsRestored) { return; }
        bThumbnailGuardsRestored = true;
        if (IsRunningCommandlet() || !UObjectInitialized())
        {
            OriginalMaterialThumbnailClass.Reset();
            OriginalInstanceThumbnailClass.Reset();
            OriginalSkeletalThumbnailClass.Reset();
            return;
        }
        UThumbnailManager& Manager = UThumbnailManager::Get();
        if (OriginalMaterialThumbnailClass.IsValid())
        {
            Manager.UnregisterCustomRenderer(UMaterial::StaticClass());
            Manager.RegisterCustomRenderer(UMaterial::StaticClass(), OriginalMaterialThumbnailClass.Get());
        }
        if (OriginalInstanceThumbnailClass.IsValid())
        {
            Manager.UnregisterCustomRenderer(UMaterialInterface::StaticClass());
            Manager.RegisterCustomRenderer(UMaterialInterface::StaticClass(), OriginalInstanceThumbnailClass.Get());
        }
        if (OriginalSkeletalThumbnailClass.IsValid())
        {
            Manager.UnregisterCustomRenderer(USkeletalMesh::StaticClass());
            Manager.RegisterCustomRenderer(USkeletalMesh::StaticClass(), OriginalSkeletalThumbnailClass.Get());
        }
        OriginalMaterialThumbnailClass.Reset();
        OriginalInstanceThumbnailClass.Reset();
        OriginalSkeletalThumbnailClass.Reset();
    }

    void OnModulesChanged(FName, EModuleChangeReason Reason)
    {
        if (Reason == EModuleChangeReason::ModuleLoaded && IsInGameThread())
        {
            DecorateRegisteredActions();
        }
    }

    void DecorateRegisteredActions()
    {
        if (bDecorating) { return; }
        TGuardValue<bool> Guard(bDecorating, true);
        FAssetToolsModule* Module = FModuleManager::GetModulePtr<FAssetToolsModule>(TEXT("AssetTools"));
        if (!Module) { return; }
        IAssetTools& Tools = Module->Get();
        TArray<TWeakPtr<IAssetTypeActions>> Registered;
        Tools.GetAssetTypeActionsList(Registered);
        for (const TWeakPtr<IAssetTypeActions>& Weak : Registered)
        {
            TSharedPtr<IAssetTypeActions> Original = Weak.Pin();
            if (!Original.IsValid() || Decorators.Contains(Original.Get()) || Original == Fallback || !Original->GetSupportedClass()) { continue; }
            if (PlainDataFallbacks.ContainsByPredicate([&Original](const TSharedRef<RebirthPreview::FUnknownObjectActions>& Action) { return &Action.Get() == Original.Get(); })) { continue; }
            // Niagara script factories downcast these actions and call their
            // extra virtual GetTypeName. Preserve their native concrete type.
            if (Original->GetSupportedClass()->IsChildOf(UNiagaraScript::StaticClass())) { continue; }
            if (Original->GetSupportedClass()->GetPathName() == TEXT("/Script/DMXPixelMappingRuntime.DMXPixelMapping")) { continue; }
            TSharedRef<RebirthPreview::FPreviewAssetActions> Action = MakeShared<RebirthPreview::FPreviewAssetActions>(Original.ToSharedRef());
            Tools.UnregisterAssetTypeActions(Original.ToSharedRef());
            Tools.RegisterAssetTypeActions(Action);
            Actions.Add(Action);
            Decorators.Add(&Action.Get());
        }
    }

    TArray<TSharedRef<RebirthPreview::FPreviewAssetActions>> Actions;
    TSet<IAssetTypeActions*> Decorators;
    TSharedPtr<RebirthPreview::FUnknownObjectActions> Fallback;
    TArray<TSharedRef<RebirthPreview::FUnknownObjectActions>> PlainDataFallbacks;
    FDelegateHandle ModulesChangedHandle;
    FDelegateHandle PreExitHandle;
    bool bDecorating = false;
    bool bThumbnailGuardsRestored = false;
    TUniquePtr<FAutoConsoleCommand> BonamikProbeCommand;
    TUniquePtr<FAutoConsoleCommand> AnimationProbeCommand;
    TUniquePtr<FAutoConsoleCommand> MaterialProbeCommand;
    TUniquePtr<FAutoConsoleCommand> PreviewCommand;
    TStrongObjectPtr<UClass> OriginalMaterialThumbnailClass;
    TStrongObjectPtr<UClass> OriginalInstanceThumbnailClass;
    TStrongObjectPtr<UClass> OriginalSkeletalThumbnailClass;
};

IMPLEMENT_MODULE(FRebirthMaterialPreviewModule, RebirthMaterialPreview)
