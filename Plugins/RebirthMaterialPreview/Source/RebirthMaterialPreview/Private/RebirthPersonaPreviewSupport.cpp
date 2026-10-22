#include "RebirthPersonaPreviewSupport.h"

#include "RebirthMaterialPreviewSafety.h"
#include "RebirthPreviewMaterialResolver.h"
#include "EditorStyleSet.h"
#include "Engine/Engine.h"
#include "Engine/SkeletalMesh.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Framework/MultiBox/MultiBoxExtender.h"
#include "GameFramework/Actor.h"
#include "HAL/IConsoleManager.h"
#include "IAnimationEditor.h"
#include "IAnimationEditorModule.h"
#include "IPersonaPreviewScene.h"
#include "IPersonaToolkit.h"
#include "ISkeletalMeshEditor.h"
#include "ISkeletalMeshEditorModule.h"
#include "ISkeletonEditor.h"
#include "ISkeletonEditorModule.h"
#include "MaterialShared.h"
#include "Materials/Material.h"
#include "Misc/PackageName.h"
#include "Modules/ModuleManager.h"
#include "PersonaModule.h"
#include "SQEX_BonamikAsset.h"
#include "UObject/Package.h"
#include "UObject/UObjectIterator.h"
#include "HAL/PlatformTime.h"

DEFINE_LOG_CATEGORY_STATIC(LogRebirthPersonaSupport, Log, All);

namespace
{
    FDelegateHandle SceneCreatedHandle;
    FDelegateHandle SkeletalMeshToolbarHandle;
    FDelegateHandle AnimationToolbarHandle;
    FDelegateHandle SkeletonToolbarHandle;
    int32 BonamikResetSerialCounter = 0;

    TAutoConsoleVariable<int32> CVarPersonaBonamik(
        TEXT("Rebirth.Bonamik.Persona"),
        1,
        TEXT("1 (default): Persona previews (skeletal mesh, animation and skeleton editors) simulate the mesh's attached Bonamik data on top of the previewed animation. 0: off. Preview only; no asset is changed."),
        ECVF_Default);

    FAutoConsoleCommand ResetBonamikCommand(
        TEXT("Rebirth.Bonamik.Reset"),
        TEXT("Restart every Persona Bonamik preview simulation from the current animated pose."),
        FConsoleCommandDelegate::CreateStatic(&RebirthPersonaPreviewSupport::ResetBonamik));

    FText BonamikTooltip(const TWeakPtr<IPersonaToolkit>& WeakToolkit)
    {
        FString Text = TEXT("Simulate this mesh's Bonamik data (hair, cloth, accessories) on top of the previewed animation. ")
            TEXT("Preview only: the mesh, its Bonamik assets and the animation are not changed. Turning it on restarts the simulation.");
        if (const TSharedPtr<IPersonaToolkit> Toolkit = WeakToolkit.Pin())
        {
            if (const URebirthPersonaPreviewMeshComponent* Component = Cast<URebirthPersonaPreviewMeshComponent>(Toolkit->GetPreviewMeshComponent()))
            {
                Text += TEXT("\n\n") + Component->GetBonamikStatusText().ToString();
            }
            else
            {
                Text += TEXT("\n\nThis preview uses another editor's own preview component, so the Bonamik preview is not available here.");
            }
        }
        return FText::FromString(Text);
    }

    TSharedRef<FExtender> MakeBonamikToolbarExtender(const TSharedRef<FUICommandList>& Commands, const TSharedRef<IPersonaToolkit>& Toolkit)
    {
        const TWeakPtr<IPersonaToolkit> WeakToolkit = Toolkit;
        TSharedRef<FExtender> Extender = MakeShared<FExtender>();
        Extender->AddToolBarExtension(TEXT("Asset"), EExtensionHook::After, Commands,
            FToolBarExtensionDelegate::CreateLambda([WeakToolkit](FToolBarBuilder& Builder)
            {
                Builder.BeginSection(TEXT("RebirthBonamik"));
                Builder.AddToolBarButton(
                    FUIAction(
                        FExecuteAction::CreateLambda([]() { RebirthPersonaPreviewSupport::SetBonamikEnabled(!RebirthPersonaPreviewSupport::IsBonamikEnabled()); }),
                        FCanExecuteAction(),
                        FIsActionChecked::CreateLambda([]() { return RebirthPersonaPreviewSupport::IsBonamikEnabled(); })),
                    NAME_None,
                    FText::FromString(TEXT("Bonamik")),
                    TAttribute<FText>::Create(TAttribute<FText>::FGetter::CreateLambda([WeakToolkit]() { return BonamikTooltip(WeakToolkit); })),
                    FSlateIcon(FEditorStyle::GetStyleSetName(), TEXT("PhysicsAssetEditor.SimulationAll")),
                    EUserInterfaceActionType::ToggleButton);
                Builder.EndSection();
            }));
        return Extender;
    }

    bool IsCookedObject(const UObject* Object)
    {
        const UPackage* Package = Object ? Object->GetOutermost() : nullptr;
        return Package && (Package->bIsCookedForEditor ||
            Package->HasAnyPackageFlags(PKG_Cooked | PKG_FilterEditorOnly));
    }

    bool CanUseMaterial(UMaterialInterface* Material, FString& Reason)
    {
        bool bCookedChain = false;
        if (!RebirthMaterialPreviewSafety::CanRender(Material, bCookedChain, Reason))
        {
            return false;
        }
        UMaterial* Base = Material->GetMaterial();
        // Do not call CheckMaterialUsage here: it can mutate/recompile originals.
        return Base && (Base->IsDefaultMaterial() || Base->GetUsageByFlag(MATUSAGE_SkeletalMesh));
    }

    void OnSceneCreated(const TSharedRef<IPersonaPreviewScene>& Scene)
    {
        if (IsRunningCommandlet() || !IsInGameThread()) { return; }
        UDebugSkelMeshComponent* Original = Scene->GetPreviewMeshComponent();
        AActor* Actor = Scene->GetActor();
        // Global notification precedes Persona's first SetPreviewMesh. Respect
        // components supplied by other toolkits and never replace a live mesh.
        if (!Original || !Actor || Original->SkeletalMesh ||
            Original->GetClass() != UDebugSkelMeshComponent::StaticClass())
        {
            UE_LOG(LogRebirthPersonaSupport, Verbose, TEXT("Persona initial component left unchanged (custom or already initialized)."));
            return;
        }

        URebirthPersonaPreviewMeshComponent* Replacement =
            NewObject<URebirthPersonaPreviewMeshComponent>(Original->GetOuter(), NAME_None, RF_Transient);
        // Persona has only assigned Mobility at this point. A property copy
        // would also copy transient animation instances owned by Original.
        // Keep fresh native defaults and let registration create our instances.
        Replacement->SetMobility(Original->Mobility);
        const FTransform Transform = Original->GetComponentTransform();
        Scene->RemoveComponent(Original);
        Scene->SetPreviewMeshComponent(Replacement);
        if (Actor->GetRootComponent() == Original) { Actor->SetRootComponent(Replacement); }
        Scene->AddComponent(Replacement, Transform);
        Original->DestroyComponent();
        UE_LOG(LogRebirthPersonaSupport, Display,
            TEXT("Persona native preview component protected before mesh assignment; animation and physics settings retained."));
    }
}

URebirthPersonaPreviewMeshComponent::URebirthPersonaPreviewMeshComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer), SafeFallbackMaterial(nullptr)
{
}

void URebirthPersonaPreviewMeshComponent::ResolvePreviewMaterials(USkeletalMesh* Mesh)
{
    SafePreviewMaterials.Reset();
    SafeFallbackMaterial = nullptr;
    bRetryMaterials = false;
    bProtectMaterials = IsCookedObject(Mesh);
    if (!Mesh) { return; }
    if (!bProtectMaterials)
    {
        for (const FSkeletalMaterial& Slot : Mesh->Materials)
        {
            const RebirthMaterialPreviewSafety::FResult Result = RebirthMaterialPreviewSafety::Evaluate(Slot.MaterialInterface);
            if (Result.bUsesCookedChain || Result.bHasUnsupportedRenderState || !Result.bParentChainValid)
            {
                bProtectMaterials = true;
                break;
            }
        }
    }
    if (!bProtectMaterials) { return; } // Authored native material behavior passes through.

    SafeFallbackMaterial = UMaterial::GetDefaultMaterial(MD_Surface);
    for (int32 Index = 0; Index < Mesh->Materials.Num(); ++Index)
    {
        const FSkeletalMaterial& Slot = Mesh->Materials[Index];
        UMaterialInterface* Source = OverrideMaterials.IsValidIndex(Index) && OverrideMaterials[Index]
            ? OverrideMaterials[Index] : Slot.MaterialInterface;
        const RebirthPreviewMaterialResolver::FResult Resolution = RebirthPreviewMaterialResolver::Resolve(Source, this);
        UMaterialInterface* Selected = Resolution.Material;
        bRetryMaterials |= Resolution.bPendingShaderResources;
        FString Reason;
        if (!Selected || !CanUseMaterial(Selected, Reason)) { Selected = SafeFallbackMaterial; }
        SafePreviewMaterials.Add(Selected);
    }
}

void URebirthPersonaPreviewMeshComponent::SetSkeletalMesh(USkeletalMesh* NewMesh, bool bReinitPose)
{
    check(IsInGameThread());
    // Resolve before Super unregisters/re-registers and constructs any proxy.
    ResolvePreviewMaterials(NewMesh);
    RetryDeadline = FPlatformTime::Seconds() + 600.0;
    NextRetryTime = FPlatformTime::Seconds() + 0.5;
    ClearBonamik();
    Super::SetSkeletalMesh(NewMesh, bReinitPose);
    InitializeBonamik(SkeletalMesh);
}

void URebirthPersonaPreviewMeshComponent::RequestMaterialRefresh()
{
    if (!bProtectMaterials) { return; }
    const double Now = FPlatformTime::Seconds();
    bRetryMaterials = true;
    NextRetryTime = Now;
    // First-time compiles of the recovered surface families can take minutes on a cold shader cache.
    RetryDeadline = FMath::Max(RetryDeadline, Now + 1800.0);
}

void URebirthPersonaPreviewMeshComponent::BeginDestroy()
{
    ClearBonamik();
    Super::BeginDestroy();
}

void URebirthPersonaPreviewMeshComponent::ClearBonamik()
{
    for (TUniquePtr<FRebirthBonamikPreviewSession>& Session : BonamikSessions)
    {
        if (Session.IsValid() && IsInGameThread()) { Session->Clear(); }
    }
    BonamikSessions.Reset();
    BonamikMesh.Reset();
    BonamikStatus.Reset();
    PendingBonamikSeconds = 0.0f;
    BonamikFailedFrames = 0;
    bBonamikRunning = false;
}

void URebirthPersonaPreviewMeshComponent::InitializeBonamik(USkeletalMesh* Mesh)
{
    ClearBonamik();
    BonamikMesh = Mesh;
    if (!Mesh || IsRunningCommandlet() || !IsInGameThread()) { return; }

    TArray<USQEX_BonamikAsset*> Assets;
    FRebirthBonamikPreviewSession::FindLoadedAssets(Mesh, Assets);
    if (Assets.Num() == 0)
    {
        BonamikStatus = TEXT("Bonamik: this mesh has no Bonamik data attached (SQEX_KBD_AssetUserData > BonamikDataList).");
        return;
    }
    TArray<FString> Skipped;
    int32 BodyCount = 0;
    for (USQEX_BonamikAsset* Asset : Assets)
    {
        TUniquePtr<FRebirthBonamikPreviewSession> Session = MakeUnique<FRebirthBonamikPreviewSession>();
        FString Status;
        if (Session->InitializeForMesh(Mesh, Asset, Status))
        {
            BodyCount += Session->GetBodyCount();
            UE_LOG(LogRebirthPersonaSupport, Display, TEXT("PersonaBonamikReady mesh=%s asset=%s bodies=%d status=%s"),
                *GetPathNameSafe(Mesh), *GetPathNameSafe(Asset), Session->GetBodyCount(), *Status);
            BonamikSessions.Add(MoveTemp(Session));
        }
        else
        {
            Skipped.Add(FString::Printf(TEXT("%s (%s)"), *GetNameSafe(Asset), *Status));
            UE_LOG(LogRebirthPersonaSupport, Warning, TEXT("PersonaBonamikUnavailable mesh=%s asset=%s reason=%s"),
                *GetPathNameSafe(Mesh), *GetPathNameSafe(Asset), *Status);
        }
    }
    if (BonamikSessions.Num() > 0)
    {
        BonamikStatus = FString::Printf(TEXT("Bonamik: simulating %d attached asset(s), %d bodies."), BonamikSessions.Num(), BodyCount);
        if (Skipped.Num() > 0) { BonamikStatus += TEXT(" Skipped: ") + FString::Join(Skipped, TEXT("; ")); }
    }
    else
    {
        BonamikStatus = TEXT("Bonamik unavailable for this mesh: ") + FString::Join(Skipped, TEXT("; "));
    }
}

FText URebirthPersonaPreviewMeshComponent::GetBonamikStatusText() const
{
    FString Text = BonamikStatus.IsEmpty() ? FString(TEXT("Bonamik: no mesh previewed.")) : BonamikStatus;
    if (BonamikSessions.Num() > 0)
    {
        Text += !RebirthPersonaPreviewSupport::IsBonamikEnabled() ? TEXT(" Currently off.")
            : bBonamikRunning ? TEXT(" Running.") : TEXT(" Waiting for the next animated pose.");
    }
    return FText::FromString(Text);
}

void URebirthPersonaPreviewMeshComponent::FinalizeBoneTransform()
{
    // A freshly evaluated pose sits in the editable buffer until Super flips it for rendering.
    if (bNeedToFlipSpaceBaseBuffers) { ApplyBonamik(); }
    Super::FinalizeBoneTransform();
}

void URebirthPersonaPreviewMeshComponent::ApplyBonamik()
{
    // Persona can deliver one long frame after a hitch; clamp instead of restarting the simulation.
    const float DeltaSeconds = FMath::Clamp(PendingBonamikSeconds, 0.0f, 0.1f);
    PendingBonamikSeconds = 0.0f;
    if (BonamikSessions.Num() == 0 || !RebirthPersonaPreviewSupport::IsBonamikEnabled() ||
        !SkeletalMesh || SkeletalMesh != BonamikMesh.Get() || !IsInGameThread())
    {
        bBonamikRunning = false;
        return;
    }
    TArray<FTransform>& Pose = GetEditableComponentSpaceTransforms();
    const FReferenceSkeleton& Ref = SkeletalMesh->RefSkeleton;
    if (Pose.Num() != Ref.GetNum())
    {
        bBonamikRunning = false;
        return;
    }

    // Rebuild the animated pose from this frame's local pose. Bones outside the current LOD's required set are not
    // re-evaluated and still hold an older (possibly simulated) value in this buffer; never feed that back in.
    TArray<FTransform> Animated = GetBoneSpaceTransforms();
    if (Animated.Num() == Pose.Num())
    {
        for (int32 Index = 0; Index < Animated.Num(); ++Index)
        {
            const int32 Parent = Ref.GetParentIndex(Index);
            if (Parent != INDEX_NONE) { Animated[Index] = Animated[Index] * Animated[Parent]; }
            Animated[Index].NormalizeRotation();
        }
    }
    else
    {
        Animated = Pose;
        for (FTransform& Transform : Animated) { Transform.NormalizeRotation(); }
    }

    const int32 ResetSerial = RebirthPersonaPreviewSupport::GetBonamikResetSerial();
    if (!bBonamikRunning || ResetSerial != BonamikResetSerial)
    {
        for (TUniquePtr<FRebirthBonamikPreviewSession>& Session : BonamikSessions) { Session->ResetSimulation(); }
        BonamikResetSerial = ResetSerial;
    }

    const FTransform SimulationToWorld = GetComponentTransform();
    TArray<FTransform> Simulated;
    bool bApplied = false;
    for (TUniquePtr<FRebirthBonamikPreviewSession>& Session : BonamikSessions)
    {
        if (Session->GetBoneCount() == Animated.Num() && Session->Simulate(DeltaSeconds, SimulationToWorld, Animated, Simulated))
        {
            Animated = MoveTemp(Simulated);
            bApplied = true;
        }
    }
    if (bApplied)
    {
        Pose = MoveTemp(Animated);
        bBonamikRunning = true;
        BonamikFailedFrames = 0;
    }
    else
    {
        bBonamikRunning = false;
        if (BonamikFailedFrames++ == 0)
        {
            UE_LOG(LogRebirthPersonaSupport, Verbose, TEXT("PersonaBonamikSkippedFrame mesh=%s (non-finite pose or non-unit component scale)"), *GetPathNameSafe(SkeletalMesh));
        }
    }
}

UMaterialInterface* URebirthPersonaPreviewMeshComponent::GetMaterial(int32 MaterialIndex) const
{
    if (bProtectMaterials)
    {
        // Renderer and streaming callers only read this GC-owned cache. Never
        // load, compile, or recursively inspect a cooked parent in this getter.
        return SafePreviewMaterials.IsValidIndex(MaterialIndex)
            ? SafePreviewMaterials[MaterialIndex] : SafeFallbackMaterial;
    }
    return Super::GetMaterial(MaterialIndex);
}

FPrimitiveSceneProxy* URebirthPersonaPreviewMeshComponent::CreateSceneProxy()
{
    // Native material/slot edits can dirty a proxy without changing its mesh.
    // Refresh only our transient cache, honoring safe component overrides.
    ResolvePreviewMaterials(SkeletalMesh);
    if (bProtectMaterials)
    {
        FString Reason;
        for (UMaterialInterface* Material : SafePreviewMaterials)
        {
            if (!CanUseMaterial(Material, Reason))
            {
                bRetryMaterials = true;
                return nullptr;
            }
        }
        if (!CanUseMaterial(SafeFallbackMaterial, Reason))
        {
            bRetryMaterials = true;
            return nullptr;
        }
        FString Choices;
        for (int32 Index = 0; Index < SafePreviewMaterials.Num(); ++Index)
        {
            if (Index) { Choices += TEXT(";"); }
            Choices += FString::Printf(TEXT("%d=%s"), Index, *GetPathNameSafe(SafePreviewMaterials[Index]));
        }
        UE_LOG(LogRebirthPersonaSupport, Display,
            TEXT("PersonaProtectedProxy mesh=%s slots=%d chosen_materials=%s pending_companions=%d native_animation_physics_settings=retained"),
            *GetPathNameSafe(SkeletalMesh), SafePreviewMaterials.Num(), *Choices, bRetryMaterials ? 1 : 0);
    }
    return Super::CreateSceneProxy();
}

void URebirthPersonaPreviewMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    // Persona evaluates the pose inside Super's tick, so the step must be known before it.
    if (FMath::IsFinite(DeltaTime) && DeltaTime > 0.0f) { PendingBonamikSeconds = FMath::Min(PendingBonamikSeconds + DeltaTime, 1.0f); }
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    const double Now = FPlatformTime::Seconds();
    if (bProtectMaterials && bRetryMaterials && Now >= NextRetryTime && Now <= RetryDeadline)
    {
        NextRetryTime = Now + 0.5;
        const TArray<UMaterialInterface*> Previous = SafePreviewMaterials;
        ResolvePreviewMaterials(SkeletalMesh);
        if (Previous != SafePreviewMaterials || !SceneProxy) { MarkRenderStateDirty(); }
    }
    else if (Now > RetryDeadline) { bRetryMaterials = false; }
}

namespace RebirthPersonaPreviewSupport
{
    bool IsBonamikEnabled()
    {
        return CVarPersonaBonamik.GetValueOnGameThread() != 0;
    }

    void SetBonamikEnabled(bool bEnabled)
    {
        if (bEnabled) { ResetBonamik(); }
        CVarPersonaBonamik->Set(bEnabled ? 1 : 0, ECVF_SetByConsole);
        UE_LOG(LogRebirthPersonaSupport, Display, TEXT("Persona Bonamik preview %s."), bEnabled ? TEXT("on") : TEXT("off"));
    }

    void ResetBonamik()
    {
        ++BonamikResetSerialCounter;
    }

    int32 GetBonamikResetSerial()
    {
        return BonamikResetSerialCounter;
    }

    void RefreshPreviewMaterials()
    {
        if (!IsInGameThread()) { return; }
        for (TObjectIterator<URebirthPersonaPreviewMeshComponent> It; It; ++It)
        {
            URebirthPersonaPreviewMeshComponent* Component = *It;
            if (IsValid(Component) && !Component->HasAnyFlags(RF_ClassDefaultObject | RF_BeginDestroyed | RF_FinishDestroyed))
            {
                Component->RequestMaterialRefresh();
            }
        }
    }

    void Register()
    {
        if (IsRunningCommandlet() || SceneCreatedHandle.IsValid()) { return; }
        FPersonaModule& Persona = FModuleManager::LoadModuleChecked<FPersonaModule>(TEXT("Persona"));
        SceneCreatedHandle = Persona.OnPreviewSceneCreated().AddStatic(&OnSceneCreated);

        // Bonamik toggle on the toolbar of every Persona editor that hosts our preview component.
        ISkeletalMeshEditorModule& MeshEditorModule = FModuleManager::LoadModuleChecked<ISkeletalMeshEditorModule>(TEXT("SkeletalMeshEditor"));
        ISkeletalMeshEditorModule::FSkeletalMeshEditorToolbarExtender MeshExtender = ISkeletalMeshEditorModule::FSkeletalMeshEditorToolbarExtender::CreateLambda(
            [](const TSharedRef<FUICommandList> Commands, TSharedRef<ISkeletalMeshEditor> Editor) { return MakeBonamikToolbarExtender(Commands, Editor->GetPersonaToolkit()); });
        SkeletalMeshToolbarHandle = MeshExtender.GetHandle();
        MeshEditorModule.GetAllSkeletalMeshEditorToolbarExtenders().Add(MeshExtender);

        IAnimationEditorModule& AnimEditorModule = FModuleManager::LoadModuleChecked<IAnimationEditorModule>(TEXT("AnimationEditor"));
        IAnimationEditorModule::FAnimationEditorToolbarExtender AnimationExtender = IAnimationEditorModule::FAnimationEditorToolbarExtender::CreateLambda(
            [](const TSharedRef<FUICommandList> Commands, TSharedRef<IAnimationEditor> Editor) { return MakeBonamikToolbarExtender(Commands, Editor->GetPersonaToolkit()); });
        AnimationToolbarHandle = AnimationExtender.GetHandle();
        AnimEditorModule.GetAllAnimationEditorToolbarExtenders().Add(AnimationExtender);

        ISkeletonEditorModule& SkelEditorModule = FModuleManager::LoadModuleChecked<ISkeletonEditorModule>(TEXT("SkeletonEditor"));
        ISkeletonEditorModule::FSkeletonEditorToolbarExtender SkeletonExtender = ISkeletonEditorModule::FSkeletonEditorToolbarExtender::CreateLambda(
            [](const TSharedRef<FUICommandList> Commands, TSharedRef<ISkeletonEditor> Editor) { return MakeBonamikToolbarExtender(Commands, Editor->GetPersonaToolkit()); });
        SkeletonToolbarHandle = SkeletonExtender.GetHandle();
        SkelEditorModule.GetAllSkeletonEditorToolbarExtenders().Add(SkeletonExtender);
    }

    void Unregister()
    {
        if (FPersonaModule* Persona = FModuleManager::GetModulePtr<FPersonaModule>(TEXT("Persona")))
        {
            Persona->OnPreviewSceneCreated().Remove(SceneCreatedHandle);
        }
        SceneCreatedHandle.Reset();
        if (ISkeletalMeshEditorModule* Module = FModuleManager::GetModulePtr<ISkeletalMeshEditorModule>(TEXT("SkeletalMeshEditor")))
        {
            Module->GetAllSkeletalMeshEditorToolbarExtenders().RemoveAll([](const ISkeletalMeshEditorModule::FSkeletalMeshEditorToolbarExtender& Candidate) { return Candidate.GetHandle() == SkeletalMeshToolbarHandle; });
        }
        if (IAnimationEditorModule* Module = FModuleManager::GetModulePtr<IAnimationEditorModule>(TEXT("AnimationEditor")))
        {
            Module->GetAllAnimationEditorToolbarExtenders().RemoveAll([](const IAnimationEditorModule::FAnimationEditorToolbarExtender& Candidate) { return Candidate.GetHandle() == AnimationToolbarHandle; });
        }
        if (ISkeletonEditorModule* Module = FModuleManager::GetModulePtr<ISkeletonEditorModule>(TEXT("SkeletonEditor")))
        {
            Module->GetAllSkeletonEditorToolbarExtenders().RemoveAll([](const ISkeletonEditorModule::FSkeletonEditorToolbarExtender& Candidate) { return Candidate.GetHandle() == SkeletonToolbarHandle; });
        }
        SkeletalMeshToolbarHandle.Reset();
        AnimationToolbarHandle.Reset();
        SkeletonToolbarHandle.Reset();
    }
}
