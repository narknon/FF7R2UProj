#include "RebirthBonamikPreviewSession.h"

#include "Components/PoseableMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/AssetUserData.h"
#include "UObject/UnrealType.h"
#include "UObject/UObjectGlobals.h"

namespace
{
    void CollectAssets(UObject* Object, TSet<UObject*>& Visited, TArray<USQEX_BonamikAsset*>& Out, int32 Depth)
    {
        if (!IsValid(Object) || Depth > 4 || Visited.Num() > 128 || Visited.Contains(Object)) return;
        Visited.Add(Object);
        if (USQEX_BonamikAsset* Asset = Cast<USQEX_BonamikAsset>(Object))
        {
            Out.AddUnique(Asset);
            return;
        }
        // Existing loaded references only. No sibling path guessing or LoadPackage.
        for (const FName Field : { FName(TEXT("BonamikDataList")), FName(TEXT("AssetUserData")) })
        {
            FArrayProperty* Array = FindFProperty<FArrayProperty>(Object->GetClass(), Field);
            FObjectPropertyBase* Inner = Array ? CastField<FObjectPropertyBase>(Array->Inner) : nullptr;
            if (!Inner) continue;
            FScriptArrayHelper Values(Array, Array->ContainerPtrToValuePtr<void>(Object));
            for (int32 Index = 0; Index < FMath::Min(Values.Num(), 128); ++Index)
                CollectAssets(Inner->GetObjectPropertyValue(Values.GetRawPtr(Index)), Visited, Out, Depth + 1);
        }
    }

    bool FinitePose(const TArray<FTransform>& Pose)
    {
        for (const FTransform& Transform : Pose)
            if (Transform.ContainsNaN() || !Transform.GetRotation().IsNormalized()) return false;
        return true;
    }

    FSQEX_BonamikLinkDesc MakeLegacyLink(const FSQEX_BonamikSimpleLinkDesc& Source, const TMap<FString, int32>& BodyIds)
    {
        FSQEX_BonamikLinkDesc Link;
        Link.m_ParentBodyName = Source.mA;
        Link.m_ChildBodyName = Source.mB;
        Link.m_ParentId = BodyIds.Contains(Source.mA) ? static_cast<uint32>(BodyIds[Source.mA]) : MAX_uint32;
        Link.m_ChildId = BodyIds.Contains(Source.mB) ? static_cast<uint32>(BodyIds[Source.mB]) : MAX_uint32;
        Link.m_LinkType = ESQEX_Bonamik_LinkType_ParentChild;
        Link.m_LinkStr = Source.mStretchedStrength;
        Link.m_LinkCompressedStr = Source.mCompressedStrength;
        Link.m_LinkParentStr = Source.mLinkParentStrength;
        Link.m_EnableJointTwist = Source.bEnableJointTwist;
        return Link;
    }
}

void FRebirthBonamikPreviewSession::FindLoadedAssets(USkeletalMesh* InMesh, TArray<USQEX_BonamikAsset*>& OutAssets)
{
    check(IsInGameThread());
    OutAssets.Reset();
    if (IsGarbageCollecting() || !IsValid(InMesh)) return;
    TSet<UObject*> Visited;
    if (const TArray<UAssetUserData*>* UserData = InMesh->GetAssetUserDataArray())
        for (UAssetUserData* Data : *UserData) CollectAssets(Data, Visited, OutAssets, 0);
}

bool FRebirthBonamikPreviewSession::Initialize(UPoseableMeshComponent* InTarget, USQEX_BonamikAsset* Source, FString& OutStatus)
{
    check(IsInGameThread());
    if (!IsValid(InTarget))
    {
        Clear();
        Status = TEXT("Bonamik preview needs a loaded mesh and its loaded physics asset.");
        OutStatus = Status;
        return false;
    }
    if (!InitializeForMesh(InTarget->SkeletalMesh, Source, OutStatus)) return false;
    Target = InTarget;
    return true;
}

bool FRebirthBonamikPreviewSession::InitializeForMesh(USkeletalMesh* InMesh, USQEX_BonamikAsset* Source, FString& OutStatus)
{
    check(IsInGameThread());
    if (IsGarbageCollecting())
    {
        OutStatus = TEXT("Bonamik preview cannot initialize during garbage collection.");
        return false;
    }
    Clear();
    auto Refuse = [&](const TCHAR* Reason)
    {
        Status = Reason;
        OutStatus = Status;
        return false;
    };
    if (!IsValid(InMesh) || !IsValid(Source))
        return Refuse(TEXT("Bonamik preview needs a loaded mesh and its loaded physics asset."));
    TArray<USQEX_BonamikAsset*> AttachedAssets;
    FindLoadedAssets(InMesh, AttachedAssets);
    if (!AttachedAssets.Contains(Source))
        return Refuse(TEXT("Bonamik preview requires a physics asset actually attached to this mesh."));
    if (Source->mBodies.Num() == 0)
        return Refuse(TEXT("Bonamik preview: this first port supports Rebirth body data; nested v2/legacy data is not yet supported."));
    if (!Source->mSceneManager.m_IsEnable || Source->mBodies.Num() > 4096 ||
        Source->mLinks.Num() + Source->mCones.Num() > 16384)
        return Refuse(TEXT("Bonamik preview refused disabled or oversized physics data."));

    const FReferenceSkeleton& Ref = InMesh->RefSkeleton;
    TArray<FName> Names;
    Names.Reserve(Ref.GetNum());
    Parents.Reserve(Ref.GetNum());
    ReferenceComponentPose = Ref.GetRefBonePose();
    for (int32 Index = 0; Index < Ref.GetNum(); ++Index)
    {
        Names.Add(Ref.GetBoneName(Index));
        Parents.Add(Ref.GetParentIndex(Index));
        if ((Index == 0 && Parents[Index] != INDEX_NONE) ||
            (Index > 0 && (Parents[Index] < 0 || Parents[Index] >= Index)))
            return Refuse(TEXT("Bonamik preview requires a parent-ordered reference skeleton."));
        if (Parents[Index] != INDEX_NONE)
            ReferenceComponentPose[Index] = ReferenceComponentPose[Index] * ReferenceComponentPose[Parents[Index]];
    }
    if (!FinitePose(ReferenceComponentPose)) return Refuse(TEXT("Bonamik preview refused a non-finite reference pose."));

    FRebirthBonamikPreviewData Snapshot;
    Snapshot.m_SceneManager = Source->mSceneManager;
    Snapshot.m_Solvers = Source->mGroups;
    Snapshot.m_TeleportDistance = Source->m_TeleportDistance;
    TMap<FString, int32> GroupIds;
    TMap<FString, int32> BodyIds;
    for (int32 Index = 0; Index < Source->mGroups.Num(); ++Index)
        GroupIds.Add(Source->mGroups[Index].m_GroupName, Index);
    TSet<FName> UniqueBodyNames;
    for (int32 Index = 0; Index < Source->mBodies.Num(); ++Index)
    {
        const FSQEX_BonamikBodyDesc& Original = Source->mBodies[Index];
        const FName Identity(*Original.mName);
        if (Identity.IsNone() || UniqueBodyNames.Contains(Identity))
            return Refuse(TEXT("Bonamik preview refused ambiguous duplicate body names."));
        UniqueBodyNames.Add(Identity);
        BodyIds.Add(Original.mName, Index);
    }
    Snapshot.m_Bodies.SetNum(Source->mBodies.Num());
    Snapshot.SourceBodyLocalTransforms.SetNum(Source->mBodies.Num());
    Snapshot.BodyAnchorDepths.Init(0, Source->mBodies.Num());
    TArray<FTransform> FlattenedBodyTransforms;
    FlattenedBodyTransforms.SetNum(Source->mBodies.Num());
    TArray<uint8> Visit;
    Visit.Init(0, Source->mBodies.Num());
    int32 AttachedBodyCount = 0;
    TFunction<bool(int32)> ResolveBody = [&](int32 Index)
    {
        if (Visit[Index] == 2) return true;
        if (Visit[Index] == 1) return false; // Authored parent cycle.
        Visit[Index] = 1;
        const FSQEX_BonamikBodyDesc& Original = Source->mBodies[Index];
        const FTransform OriginalLocal(Original.m_LocalRotation, Original.m_LocalTransform, FVector::OneVector);
        if (OriginalLocal.ContainsNaN() || !Original.m_LocalRotation.IsNormalized() ||
            Original.m_LocalTransform.SizeSquared() > FMath::Square(1000.0f) || !FMath::IsFinite(Original.m_Radius) ||
            !GroupIds.Contains(Original.mGroupName)) return false;
        FSQEX_BonamikBodyDesc Body = Original;
        Body.m_Index = Index;
        Body.m_GroupId = GroupIds[Original.mGroupName];
        const int32 Bone = Ref.FindBoneIndex(FName(*Original.mParentName));
        const int32* ParentBody = BodyIds.Find(Original.mParentName);
        if (Bone != INDEX_NONE && ParentBody) return false;
        FTransform FlattenedLocal = OriginalLocal;
        if (Bone != INDEX_NONE) Body.m_JointName = Original.mParentName;
        else if (ParentBody)
        {
            // These are exact authored body attachments, never invented bone remaps.
            // The first port supports only kinematic child attachments.
            if (!Original.m_IsKinematic || !ResolveBody(*ParentBody)) return false;
            Body.m_JointName = Snapshot.m_Bodies[*ParentBody].m_JointName;
            FlattenedLocal = OriginalLocal * FlattenedBodyTransforms[*ParentBody];
            Snapshot.BodyAnchorDepths[Index] = Snapshot.BodyAnchorDepths[*ParentBody] + 1;
            ++AttachedBodyCount;
        }
        else return false;
        FlattenedLocal.NormalizeRotation();
        if (FlattenedLocal.ContainsNaN() || FlattenedLocal.GetTranslation().SizeSquared() > FMath::Square(1000.0f)) return false;
        Body.m_LocalTransform = FlattenedLocal.GetTranslation();
        Body.m_LocalRotation = FlattenedLocal.GetRotation();
        if (Source->mGroups.IsValidIndex(Body.m_GroupId) && !Source->mGroups[Body.m_GroupId].m_IsEnable)
            Body.m_IsKinematic = true;
        // Legacy preview tuning fields are absent in Rebirth. Retain its documented
        // conservative custom defaults; never write normalized values to Source.
        Snapshot.m_Bodies[Index] = Body;
        Snapshot.SourceBodyLocalTransforms[Index] = OriginalLocal;
        FlattenedBodyTransforms[Index] = FlattenedLocal;
        Visit[Index] = 2;
        return true;
    };
    for (int32 Index = 0; Index < Source->mBodies.Num(); ++Index)
        if (!ResolveBody(Index)) return Refuse(TEXT("Bonamik preview refused an unresolved, cyclic or invalid authored body anchor."));

    // Rebirth's stored scene vector is SDK Y-up. The preview mesh and component
    // are UE Z-up, in centimeters. Convert only global scene vectors; bone-local
    // offsets and rotations above remain in their authored bone frames.
    const FVector RawGravity = Snapshot.m_SceneManager.m_Gravity;
    if (RawGravity.ContainsNaN() || Snapshot.m_SceneManager.m_WindForce.ContainsNaN())
        return Refuse(TEXT("Bonamik preview refused non-finite scene acceleration."));
    Snapshot.m_SceneManager.m_Gravity = FVector(RawGravity.X, -RawGravity.Z, RawGravity.Y);
    const FVector RawWind = Snapshot.m_SceneManager.m_WindForce;
    Snapshot.m_SceneManager.m_WindForce = FVector(RawWind.X, -RawWind.Z, RawWind.Y);
    Snapshot.bSceneVectorsAreUECentimeters = true;
    Snapshot.AuthoredShapes = Source->mShapes;
    Snapshot.AuthoredCliques = Source->mCollisionCliques;
    for (const FSQEX_BonamikSimpleLinkDesc& Link : Source->mLinks)
        Snapshot.m_Links.Add(MakeLegacyLink(Link, BodyIds));
    for (const FSQEX_BonamikConeLinkDesc& Cone : Source->mCones)
    {
        FSQEX_BonamikLinkDesc Link = MakeLegacyLink(Cone, BodyIds);
        Link.m_EnableCone = true;
        Link.m_EnableConeAnimation = Cone.bEnableConeAnimation;
        Link.m_LimitY = Cone.mLimitY;
        Link.m_LimitZ = Cone.mLimitZ;
        Link.m_ConeInnerStr = Cone.mInnerConeStr;
        Link.m_ConeOuterStr = Cone.mOuterConeStr;
        Snapshot.m_Links.Add(Link);
    }
    TArray<FRebirthBonamikPreviewData> Snapshots;
    Snapshots.Add(MoveTemp(Snapshot));
    const TArray<FRebirthBonamikPreviewCollider> NoColliders;
    if (!Solver.Rebuild(Snapshots, Names, Parents, NoColliders))
        return Refuse(TEXT("Bonamik preview has no unambiguous mapped dynamic bone owners."));
    Mesh = InMesh;
    LastAnimatedComponentPose = ReferenceComponentPose;
    Settings = FRebirthBonamikPreviewSettings();
    Settings.MaxSubsteps = 8;
    Settings.MaxConstraintIterations = 8;
    Settings.bEnableCollisions = true;
    Settings.bEnableGroundCollision = false;
    Settings.bOverrideGravity = true; // Bypass inherited heuristic acceleration scaling.
    Settings.GravityOverride = FVector(RawGravity.X, -RawGravity.Z, RawGravity.Y);
    Status = FString::Printf(TEXT("Custom Bonamik-data preview: %d dynamic bones; %d exact body attachments; %d authored primitive shapes, %d filtered contact pairs. Sampled contacts, inverse-volume containment, single-body plane axes and clique policy are custom interpretations; tapered/concave capsules, v2, advanced wind and retail solver parity remain unsupported."),
        Solver.GetAffectedBoneIndices().Num(), AttachedBodyCount, Solver.GetAuthoredShapeCount(), Solver.GetAuthoredCollisionPairCount());
    OutStatus = Status;
    return true;
}

void FRebirthBonamikPreviewSession::ResetSimulation()
{
    check(IsInGameThread());
    Solver.ResetSimulation();
    if (IsGarbageCollecting()) return;
    UPoseableMeshComponent* Component = Target.Get();
    if (Component && Component->SkeletalMesh == Mesh.Get() && LastAnimatedComponentPose.Num() == Parents.Num())
    {
        TArray<FTransform> Local = LastAnimatedComponentPose;
        for (int32 Index = 0; Index < Local.Num(); ++Index)
            if (Parents[Index] != INDEX_NONE)
                Local[Index] = LastAnimatedComponentPose[Index].GetRelativeTransform(LastAnimatedComponentPose[Parents[Index]]);
        Component->BoneSpaceTransforms = MoveTemp(Local);
        Component->MarkRefreshTransformDirty();
        Component->RefreshBoneTransforms();
    }
}

void FRebirthBonamikPreviewSession::Clear()
{
    check(IsInGameThread());
    ResetSimulation();
    Solver.Reset();
    Target.Reset();
    Mesh.Reset();
    Parents.Reset();
    ReferenceComponentPose.Reset();
    LastAnimatedComponentPose.Reset();
    Status.Reset();
}

bool FRebirthBonamikPreviewSession::Simulate(float DeltaSeconds, const FTransform& ComponentToWorld,
    const TArray<FTransform>& AnimatedComponentPose, TArray<FTransform>& OutComponentPose)
{
    check(IsInGameThread());
    if (IsGarbageCollecting() || !Solver.IsReady() || AnimatedComponentPose.Num() != Parents.Num() ||
        !FinitePose(AnimatedComponentPose)) return false;
    if (!FMath::IsFinite(DeltaSeconds) || DeltaSeconds < 0.0f || DeltaSeconds > 0.25f)
    {
        Solver.ResetSimulation();
        return false;
    }
    // NoScale offsets in the inherited solver require unit preview scale.
    if (ComponentToWorld.ContainsNaN() || !ComponentToWorld.GetScale3D().Equals(FVector::OneVector, 0.001f))
    {
        Solver.ResetSimulation();
        return false;
    }
    LastAnimatedComponentPose = AnimatedComponentPose; // Never feed simulated output back as animation input.
    TArray<FTransform> AnimatedWorld = AnimatedComponentPose;
    for (FTransform& Transform : AnimatedWorld) Transform = Transform * ComponentToWorld;
    TArray<FTransform> SimulatedWorld = AnimatedWorld;
    Solver.Evaluate(FMath::Min(DeltaSeconds, 0.1f), AnimatedWorld, SimulatedWorld, Settings);
    TSet<int32> OwnedBones;
    for (int32 Index : Solver.GetAffectedBoneIndices()) OwnedBones.Add(Index);
    TArray<FTransform> FinalComponent = AnimatedComponentPose;
    for (int32 Index = 0; Index < Parents.Num(); ++Index)
    {
        const int32 Parent = Parents[Index];
        const FTransform AnimatedLocal = Parent == INDEX_NONE ? AnimatedComponentPose[Index] :
            AnimatedComponentPose[Index].GetRelativeTransform(AnimatedComponentPose[Parent]);
        if (OwnedBones.Contains(Index))
            FinalComponent[Index] = SimulatedWorld[Index].GetRelativeTransform(ComponentToWorld);
        else
            FinalComponent[Index] = Parent == INDEX_NONE ? AnimatedLocal : AnimatedLocal * FinalComponent[Parent];
        FinalComponent[Index].NormalizeRotation();
    }
    if (!FinitePose(FinalComponent)) { Solver.ResetSimulation(); return false; }
    OutComponentPose = MoveTemp(FinalComponent);
    return true;
}

bool FRebirthBonamikPreviewSession::TickAndApply(float DeltaSeconds, const TArray<FTransform>& AnimatedComponentPose)
{
    check(IsInGameThread());
    if (IsGarbageCollecting()) return false;
    UPoseableMeshComponent* Component = Target.Get();
    if (!Component || Component->SkeletalMesh != Mesh.Get()) return false;
    TArray<FTransform> FinalComponent;
    if (!Simulate(DeltaSeconds, Component->GetComponentTransform(), AnimatedComponentPose, FinalComponent))
    {
        if (Solver.IsReady() && AnimatedComponentPose.Num() == Parents.Num()) ResetSimulation();
        return false;
    }
    TArray<FTransform> FinalLocal = FinalComponent;
    for (int32 Index = 0; Index < Parents.Num(); ++Index)
    {
        const int32 Parent = Parents[Index];
        FinalLocal[Index] = Parent == INDEX_NONE ? FinalComponent[Index] :
            FinalComponent[Index].GetRelativeTransform(FinalComponent[Parent]);
        FinalLocal[Index].NormalizeRotation();
    }
    if (!FinitePose(FinalLocal)) { ResetSimulation(); return false; }
    // The component is transient and viewport-owned; no source mesh/BNM/skeleton writes.
    Component->BoneSpaceTransforms = MoveTemp(FinalLocal);
    Component->MarkRefreshTransformDirty();
    Component->RefreshBoneTransforms();
    return true;
}
