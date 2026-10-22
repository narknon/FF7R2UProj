#include "RebirthBonamikPreviewSolver.h"

#include "ESQEX_Bonamik_ConstraintType.h"
#include "ESQEX_Bonamik_LinkType.h"
#include "SQEX_BonamikAsset.h"
#include "SQEX_BonamikBodyDesc.h"
#include "SQEX_BonamikLinkDesc.h"
#include "SQEX_BonamikPlaneDesc.h"
#include "SQEX_BonamikSceneManagerDesc.h"
#include "SQEX_BonamikShapeMatchingDesc.h"
#include "SQEX_BonamikSolverDesc.h"
#include "PhysicsEngine/BoxElem.h"
#include "PhysicsEngine/SphereElem.h"
#include "PhysicsEngine/SphylElem.h"

namespace
{
    FName BonamikPreviewBoneName(const FString& InName)
    {
        FString CleanName = InName;
        CleanName.TrimStartAndEndInline();
        if (CleanName.IsEmpty() || CleanName.Equals(TEXT("None"), ESearchCase::IgnoreCase))
        {
            return NAME_None;
        }
        return FName(*CleanName.Left(NAME_SIZE - 1));
    }

    float NormalizeStrength(float Value, float DefaultValue)
    {
        Value = FMath::Abs(Value);
        if (!FMath::IsFinite(Value) || Value <= KINDA_SMALL_NUMBER)
        {
            return DefaultValue;
        }
        if (Value > 1.0f)
        {
            Value *= 0.01f;
        }
        return FMath::Clamp(Value, 0.0f, 1.0f);
    }

    float NormalizeRadius(float Value)
    {
        Value = FMath::Abs(Value);
        if (!FMath::IsFinite(Value) || Value <= KINDA_SMALL_NUMBER)
        {
            return 1.5f;
        }
        if (Value <= 0.25f)
        {
            Value *= 100.0f;
        }
        return FMath::Clamp(Value, 0.25f, 30.0f);
    }

    float NormalizeDisplacement(float Value)
    {
        Value = FMath::Abs(Value);
        if (!FMath::IsFinite(Value) || Value <= KINDA_SMALL_NUMBER)
        {
            return 40.0f;
        }
        if (Value <= 4.0f)
        {
            Value *= 30.0f;
        }
        return FMath::Clamp(Value, 4.0f, 250.0f);
    }

    FVector NormalizeAcceleration(const FVector& Value, const FVector& DefaultValue)
    {
        if (Value.ContainsNaN() || Value.IsNearlyZero())
        {
            return DefaultValue;
        }

        FVector Converted = Value;
        if (FMath::Abs(Value.Y) > FMath::Abs(Value.Z) * 2.0f)
        {
            Converted = FVector(Value.X, Value.Z, Value.Y);
        }
        if (Converted.Size() < 100.0f)
        {
            Converted *= 100.0f;
        }
        return Converted.GetClampedToMaxSize(10000.0f);
    }

    FVector SafeLocalOffset(const FVector& Value)
    {
        if (Value.ContainsNaN() || Value.SizeSquared() > FMath::Square(1000.0f))
        {
            return FVector::ZeroVector;
        }
        return Value;
    }

    bool ResolveSphereCollision(
        const FKSphereElem& Sphere,
        const FTransform& BodyTransform,
        float ParticleRadius,
        FVector& InOutLocation,
        FVector& OutNormal)
    {
        const FKSphereElem ScaledSphere = Sphere.GetFinalScaled(BodyTransform.GetScale3D(), FTransform::Identity);
        const FVector Center = BodyTransform.TransformPositionNoScale(ScaledSphere.Center);
        const float RequiredDistance = FMath::Max(0.0f, ScaledSphere.Radius) + ParticleRadius;
        FVector Delta = InOutLocation - Center;
        if (Delta.SizeSquared() >= FMath::Square(RequiredDistance))
        {
            return false;
        }
        if (!Delta.Normalize())
        {
            Delta = BodyTransform.TransformVectorNoScale(FVector::UpVector).GetSafeNormal();
            if (Delta.IsNearlyZero())
            {
                Delta = FVector::UpVector;
            }
        }
        OutNormal = Delta;
        InOutLocation = Center + Delta * RequiredDistance;
        return true;
    }

    bool ResolveCapsuleCollision(
        const FKSphylElem& Capsule,
        const FTransform& BodyTransform,
        float ParticleRadius,
        FVector& InOutLocation,
        FVector& OutNormal)
    {
        const FKSphylElem ScaledCapsule = Capsule.GetFinalScaled(BodyTransform.GetScale3D(), FTransform::Identity);
        const FTransform CapsuleTransform = Capsule.GetTransform() * BodyTransform;
        const float HalfLength = FMath::Max(0.0f, ScaledCapsule.Length * 0.5f);
        const FVector SegmentStart = CapsuleTransform.TransformPositionNoScale(FVector(0.0f, 0.0f, -HalfLength));
        const FVector SegmentEnd = CapsuleTransform.TransformPositionNoScale(FVector(0.0f, 0.0f, HalfLength));
        const FVector ClosestPoint = FMath::ClosestPointOnSegment(InOutLocation, SegmentStart, SegmentEnd);
        const float RequiredDistance = FMath::Max(0.0f, ScaledCapsule.Radius) + ParticleRadius;
        FVector Delta = InOutLocation - ClosestPoint;
        if (Delta.SizeSquared() >= FMath::Square(RequiredDistance))
        {
            return false;
        }
        if (!Delta.Normalize())
        {
            Delta = CapsuleTransform.TransformVectorNoScale(FVector::ForwardVector).GetSafeNormal();
            if (Delta.IsNearlyZero())
            {
                Delta = FVector::ForwardVector;
            }
        }
        OutNormal = Delta;
        InOutLocation = ClosestPoint + Delta * RequiredDistance;
        return true;
    }

    bool ResolveBoxCollision(
        const FKBoxElem& Box,
        const FTransform& BodyTransform,
        float ParticleRadius,
        FVector& InOutLocation,
        FVector& OutNormal)
    {
        const FKBoxElem ScaledBox = Box.GetFinalScaled(BodyTransform.GetScale3D(), FTransform::Identity);
        const FTransform BoxTransform = Box.GetTransform() * BodyTransform;
        FVector LocalLocation = BoxTransform.InverseTransformPositionNoScale(InOutLocation);
        const FVector HalfExtent(
            FMath::Max(0.0f, ScaledBox.X * 0.5f) + ParticleRadius,
            FMath::Max(0.0f, ScaledBox.Y * 0.5f) + ParticleRadius,
            FMath::Max(0.0f, ScaledBox.Z * 0.5f) + ParticleRadius);
        if (FMath::Abs(LocalLocation.X) >= HalfExtent.X ||
            FMath::Abs(LocalLocation.Y) >= HalfExtent.Y ||
            FMath::Abs(LocalLocation.Z) >= HalfExtent.Z)
        {
            return false;
        }

        const FVector FaceDistance = HalfExtent - LocalLocation.GetAbs();
        FVector LocalNormal = FVector::ZeroVector;
        if (FaceDistance.X <= FaceDistance.Y && FaceDistance.X <= FaceDistance.Z)
        {
            LocalNormal.X = LocalLocation.X < 0.0f ? -1.0f : 1.0f;
            LocalLocation.X = LocalNormal.X * HalfExtent.X;
        }
        else if (FaceDistance.Y <= FaceDistance.Z)
        {
            LocalNormal.Y = LocalLocation.Y < 0.0f ? -1.0f : 1.0f;
            LocalLocation.Y = LocalNormal.Y * HalfExtent.Y;
        }
        else
        {
            LocalNormal.Z = LocalLocation.Z < 0.0f ? -1.0f : 1.0f;
            LocalLocation.Z = LocalNormal.Z * HalfExtent.Z;
        }

        OutNormal = BoxTransform.TransformVectorNoScale(LocalNormal).GetSafeNormal();
        InOutLocation = BoxTransform.TransformPositionNoScale(LocalLocation);
        return !OutNormal.IsNearlyZero();
    }

    bool ResolveConvexBoundsCollision(
        const FKConvexElem& Convex,
        const FTransform& BodyTransform,
        float ParticleRadius,
        FVector& InOutLocation,
        FVector& OutNormal)
    {
        if (!Convex.ElemBox.IsValid)
        {
            return false;
        }

        const FBox Bounds = Convex.CalcAABB(BodyTransform, FVector::OneVector).ExpandBy(ParticleRadius);
        if (!Bounds.IsInside(InOutLocation))
        {
            return false;
        }

        const FVector Original = InOutLocation;
        const FVector ToMin = Original - Bounds.Min;
        const FVector ToMax = Bounds.Max - Original;
        float ClosestDistance = ToMin.X;
        OutNormal = -FVector::ForwardVector;
        FVector Resolved = Original;
        Resolved.X = Bounds.Min.X;
        if (ToMax.X < ClosestDistance)
        {
            ClosestDistance = ToMax.X;
            OutNormal = FVector::ForwardVector;
            Resolved = Original;
            Resolved.X = Bounds.Max.X;
        }
        if (ToMin.Y < ClosestDistance)
        {
            ClosestDistance = ToMin.Y;
            OutNormal = -FVector::RightVector;
            Resolved = Original;
            Resolved.Y = Bounds.Min.Y;
        }
        if (ToMax.Y < ClosestDistance)
        {
            ClosestDistance = ToMax.Y;
            OutNormal = FVector::RightVector;
            Resolved = Original;
            Resolved.Y = Bounds.Max.Y;
        }
        if (ToMin.Z < ClosestDistance)
        {
            ClosestDistance = ToMin.Z;
            OutNormal = -FVector::UpVector;
            Resolved = Original;
            Resolved.Z = Bounds.Min.Z;
        }
        if (ToMax.Z < ClosestDistance)
        {
            OutNormal = FVector::UpVector;
            Resolved = Original;
            Resolved.Z = Bounds.Max.Z;
        }
        InOutLocation = Resolved;
        return true;
    }

    bool ResolveAggregateCollision(
        const FKAggregateGeom& Geometry,
        const FTransform& BodyTransform,
        float ParticleRadius,
        FVector& InOutLocation,
        FVector& OutNormal)
    {
        bool bResolved = false;
        for (const FKSphereElem& Sphere : Geometry.SphereElems)
        {
            bResolved |= ResolveSphereCollision(Sphere, BodyTransform, ParticleRadius, InOutLocation, OutNormal);
        }
        for (const FKSphylElem& Capsule : Geometry.SphylElems)
        {
            bResolved |= ResolveCapsuleCollision(Capsule, BodyTransform, ParticleRadius, InOutLocation, OutNormal);
        }
        for (const FKBoxElem& Box : Geometry.BoxElems)
        {
            bResolved |= ResolveBoxCollision(Box, BodyTransform, ParticleRadius, InOutLocation, OutNormal);
        }
        for (const FKConvexElem& Convex : Geometry.ConvexElems)
        {
            bResolved |= ResolveConvexBoundsCollision(Convex, BodyTransform, ParticleRadius, InOutLocation, OutNormal);
        }
        return bResolved;
    }
}

FRebirthBonamikPreviewSolver::FParticle::FParticle()
    : BoneIndex(INDEX_NONE)
    , SkeletonParentBoneIndex(INDEX_NONE)
    , PrimaryParentBoneIndex(INDEX_NONE)
    , PrimaryParentParticleIndex(INDEX_NONE)
    , SimLocation(FVector::ZeroVector)
    , PreviousLocation(FVector::ZeroVector)
    , Velocity(FVector::ZeroVector)
    , LastAnimatedLocation(FVector::ZeroVector)
    , LocalOffset(FVector::ZeroVector)
    , Stiffness(45.0f)
    , Damping(8.0f)
    , MaxDisplacement(40.0f)
    , CollisionRadius(1.5f)
    , InverseMass(1.0f)
    , Friction(0.15f)
    , Restitution(0.0f)
    , WindDrag(0.0f)
    , AdditionalConstraintRadius(0.0f)
    , GroupId(0)
    , SourceCount(1)
    , bCollisionEnabled(true)
    , bSelfCollision(false)
    , bSpringConstraint(false)
    , bKinematic(false)
    , bInitialized(false)
{
}

FRebirthBonamikPreviewSolver::FLink::FLink()
    : ParentParticleIndex(INDEX_NONE)
    , ChildParticleIndex(INDEX_NONE)
    , RestLength(0.0f)
    , Stiffness(0.65f)
    , Damping(0.05f)
    , ConeLimitRadians(PI)
    , ConeStiffness(0.5f)
    , PinStrength(0.0f)
    , PinRadius(0.0f)
    , LinkType(static_cast<uint8>(ESQEX_Bonamik_LinkType_ParentChild))
    , bEnableCone(false)
    , bSelfCollision(false)
{
}

FRebirthBonamikPreviewSolver::FPlane::FPlane()
    : ParticleA(INDEX_NONE)
    , ParticleB(INDEX_NONE)
    , ParticleC(INDEX_NONE)
    , Stiffness(0.25f)
    , Thickness(0.0f)
    , Offset(0.0f)
    , GroupId(0)
    , bCollision(false)
{
}

FRebirthBonamikPreviewSolver::FRebirthBonamikPreviewSolver()
    : AuthoredGravity(0.0f, 0.0f, -980.0f)
    , AuthoredWind(FVector::ZeroVector)
    , AuthoredStep(1.0f / 60.0f)
    , AuthoredTeleportDistance(100.0f)
    , TimeAccumulator(0.0f)
    , AuthoredSubsteps(1)
    , AuthoredConstraintIterations(3)
    , bReady(false)
{
}

void FRebirthBonamikPreviewSolver::Reset()
{
    AuthoredCollision.Reset();
    AttachmentOrder.Reset();
    BodyRotations.Reset();
    Particles.Reset();
    Links.Reset();
    Planes.Reset();
    ShapeRegions.Reset();
    RuntimeColliders.Reset();
    AffectedBoneIndices.Reset();
    ParticleIndexByBoneIndex.Reset();
    AuthoredGravity = FVector(0.0f, 0.0f, -980.0f);
    AuthoredWind = FVector::ZeroVector;
    AuthoredStep = 1.0f / 60.0f;
    AuthoredTeleportDistance = 100.0f;
    TimeAccumulator = 0.0f;
    AuthoredSubsteps = 1;
    AuthoredConstraintIterations = 3;
    bReady = false;
}

void FRebirthBonamikPreviewSolver::ResetSimulation()
{
    TimeAccumulator = 0.0f;
    for (FParticle& Particle : Particles)
    {
        Particle.SimLocation = FVector::ZeroVector;
        Particle.PreviousLocation = FVector::ZeroVector;
        Particle.Velocity = FVector::ZeroVector;
        Particle.LastAnimatedLocation = FVector::ZeroVector;
        Particle.bInitialized = false;
    }
    for (FLink& Link : Links)
    {
        Link.RestLength = 0.0f;
    }
}

bool FRebirthBonamikPreviewSolver::Rebuild(
    const TArray<FRebirthBonamikPreviewData>& Assets,
    const TArray<FName>& BoneNames,
    const TArray<int32>& ParentBoneIndices,
    const TArray<FRebirthBonamikPreviewCollider>& Colliders)
{
    Reset();
    if (BoneNames.Num() == 0 || BoneNames.Num() > 8192 ||
        ParentBoneIndices.Num() != BoneNames.Num() || Assets.Num() > 16)
    {
        return false;
    }

    TMap<FName, int32> BoneIndexByName;
    for (int32 BoneIndex = 0; BoneIndex < BoneNames.Num(); ++BoneIndex)
    {
        if (ParentBoneIndices[BoneIndex] >= BoneIndex || ParentBoneIndices[BoneIndex] < INDEX_NONE ||
            (BoneIndex > 0 && ParentBoneIndices[BoneIndex] == INDEX_NONE))
        {
            return false;
        }
        if (BoneNames[BoneIndex] != NAME_None && !BoneIndexByName.Contains(BoneNames[BoneIndex]))
        {
            BoneIndexByName.Add(BoneNames[BoneIndex], BoneIndex);
        }
    }

    // Distinct authored body points may share a mesh bone. Only one dynamic
    // body may own an output transform; kinematic collider points stay distinct.
    TSet<int32> OwnedDynamicBones;
    TSet<uint64> LinkKeys;
    bool bHasAuthoredStep = false;
    for (const FRebirthBonamikPreviewData& Snapshot : Assets)
    {
        const FRebirthBonamikPreviewData* Asset = &Snapshot;
        if (Asset->m_Bodies.Num() > 4096 || Asset->m_Links.Num() > 16384 ||
            Asset->m_Planes.Num() > 4096 || Asset->m_ShapeMatchings.Num() > 1024)
        {
            Reset();
            return false;
        }

        const FSQEX_BonamikSceneManagerDesc& Scene = Asset->m_SceneManager;
        AuthoredGravity = Asset->bSceneVectorsAreUECentimeters ? Scene.m_Gravity : NormalizeAcceleration(Scene.m_Gravity, AuthoredGravity);
        AuthoredWind += Asset->bSceneVectorsAreUECentimeters ? Scene.m_WindForce : NormalizeAcceleration(Scene.m_WindForce, FVector::ZeroVector);
        AuthoredSubsteps = FMath::Max(AuthoredSubsteps, FMath::Clamp(static_cast<int32>(Scene.m_SubStep), 1, 8));
        if (FMath::IsFinite(Scene.m_Dt) && Scene.m_Dt > KINDA_SMALL_NUMBER && Scene.m_Dt < 0.1f)
        {
            AuthoredStep = bHasAuthoredStep ? FMath::Min(AuthoredStep, Scene.m_Dt) : Scene.m_Dt;
            bHasAuthoredStep = true;
        }
        if (FMath::IsFinite(Asset->m_TeleportDistance) && Asset->m_TeleportDistance > KINDA_SMALL_NUMBER)
        {
            AuthoredTeleportDistance = FMath::Max(AuthoredTeleportDistance, Asset->m_TeleportDistance);
        }
        for (const FSQEX_BonamikSolverDesc& Solver : Asset->m_Solvers)
        {
            if (!Solver.m_IsEnable)
            {
                continue;
            }
            const int32 Iterations = FMath::Max(
                static_cast<int32>(Solver.m_SolverIter),
                FMath::Max(
                    static_cast<int32>(Solver.m_ConsIter),
                    FMath::Max(static_cast<int32>(Solver.m_LinkIter), static_cast<int32>(Solver.m_ConeIter))));
            AuthoredConstraintIterations = FMath::Max(AuthoredConstraintIterations, FMath::Clamp(Iterations, 1, 16));
        }

        TMap<int32, int32> ParticleByBodyId;
        TMap<FName, int32> ParticleByBodyName;
        for (int32 BodyArrayIndex = 0; BodyArrayIndex < Asset->m_Bodies.Num(); ++BodyArrayIndex)
        {
            const FSQEX_BonamikBodyDesc& Body = Asset->m_Bodies[BodyArrayIndex];
            const FName JointName = BonamikPreviewBoneName(Body.m_JointName);
            const int32* BoneIndexPtr = BoneIndexByName.Find(JointName);
            if (!BoneIndexPtr)
            {
                continue;
            }

            const int32 BoneIndex = *BoneIndexPtr;
            if (!Body.m_IsKinematic && OwnedDynamicBones.Contains(BoneIndex))
            {
                Reset(); // Ambiguous bone ownership: refuse instead of averaging.
                return false;
            }
            int32 ParticleIndex = INDEX_NONE;
                FParticle Particle;
                ParticleIndex = Particles.Num();
                Particle.BoneIndex = BoneIndex;
                Particle.SkeletonParentBoneIndex = ParentBoneIndices[BoneIndex];
                Particle.Stiffness = 20.0f + NormalizeStrength(Body.m_LocalTransCoeff, 0.25f) * 80.0f;
                Particle.Damping = FMath::Clamp(3.0f + FMath::Abs(Body.m_Damping) * 18.0f, 3.0f, 30.0f);
                Particle.MaxDisplacement = NormalizeDisplacement(Body.m_MaxLocalTrans);
                Particle.CollisionRadius = NormalizeRadius(Body.m_Radius);
                Particle.InverseMass = Body.m_Mass > KINDA_SMALL_NUMBER
                    ? 1.0f / FMath::Clamp(Body.m_Mass, 0.001f, 10000.0f)
                    : 1.0f;
                Particle.Friction = FMath::Clamp(0.15f + FMath::Abs(Body.m_Friction) * 0.7f, 0.0f, 0.95f);
                Particle.Restitution = FMath::Clamp(FMath::Abs(Body.m_Bounciness), 0.0f, 0.5f);
                Particle.WindDrag = NormalizeStrength(Body.m_WindDrag, 0.0f);
                Particle.AdditionalConstraintRadius = NormalizeRadius(Body.m_AddiConstRad);
                Particle.bSpringConstraint = Body.m_AddiConstType == ESQEX_Bonamik_ConstraintType_Spring;
                Particle.bKinematic = Body.m_IsKinematic;
                Particle.bCollisionEnabled = Body.m_IsCollision || !Body.m_IsKinematic;
                Particle.bSelfCollision = Body.m_ColShape == ESQEX_Bonamik_CollisionShape_Self_Collision;
                Particle.GroupId = Body.m_GroupId;
                Particle.LocalOffset = SafeLocalOffset(Body.m_LocalTransform);
                Particle.LocalRotation = Body.m_LocalRotation;
                Particle.AuthoredRadius = FMath::Clamp(FMath::Abs(Body.m_Radius), 0.0f, 200.0f);
                if (Asset->SourceBodyLocalTransforms.IsValidIndex(BodyArrayIndex))
                    Particle.AnchorLocalTransform = Asset->SourceBodyLocalTransforms[BodyArrayIndex];
                if (Asset->BodyAnchorDepths.IsValidIndex(BodyArrayIndex))
                    Particle.AnchorDepth = Asset->BodyAnchorDepths[BodyArrayIndex];
                Particles.Add(Particle);
                if (!Body.m_IsKinematic)
                {
                    OwnedDynamicBones.Add(BoneIndex);
                    ParticleIndexByBoneIndex.Add(BoneIndex, ParticleIndex);
                }

            ParticleByBodyId.Add(BodyArrayIndex, ParticleIndex);
            ParticleByBodyId.Add(static_cast<int32>(Body.m_Index), ParticleIndex);
            const FName AuthoredBodyName = BonamikPreviewBoneName(Body.mName);
            if (AuthoredBodyName != NAME_None)
            {
                ParticleByBodyName.Add(AuthoredBodyName, ParticleIndex);
            }
            if (JointName != NAME_None && !ParticleByBodyName.Contains(JointName))
            {
                ParticleByBodyName.Add(JointName, ParticleIndex);
            }
        }

        for (int32 BodyIndex = 0; BodyIndex < Asset->m_Bodies.Num(); ++BodyIndex)
        {
            const int32* Child = ParticleByBodyId.Find(BodyIndex);
            const int32* Parent = ParticleByBodyName.Find(FName(*Asset->m_Bodies[BodyIndex].mParentName));
            if (Child && Parent && *Child != *Parent && Particles[*Child].bKinematic && Particles[*Child].AnchorDepth > 0)
            {
                Particles[*Child].AnchorParentParticleIndex = *Parent;
                AttachmentOrder.Add(*Child);
            }
        }
        if (!AuthoredCollision.AddAsset(Asset->AuthoredShapes, Asset->AuthoredCliques, ParticleByBodyName))
        {
            Reset();
            return false;
        }
        const auto ResolveParticle = [&ParticleByBodyId, &ParticleByBodyName](int32 BodyId, const FString& BodyName) -> int32
        {
            const FName Name = BonamikPreviewBoneName(BodyName);
            if (const int32* NamedParticle = ParticleByBodyName.Find(Name))
            {
                return *NamedParticle;
            }
            if (const int32* IdParticle = ParticleByBodyId.Find(BodyId))
            {
                return *IdParticle;
            }
            return INDEX_NONE;
        };

        for (const FSQEX_BonamikLinkDesc& SourceLink : Asset->m_Links)
        {
            const int32 ParentParticle = ResolveParticle(static_cast<int32>(SourceLink.m_ParentId), SourceLink.m_ParentBodyName);
            const int32 ChildParticle = ResolveParticle(static_cast<int32>(SourceLink.m_ChildId), SourceLink.m_ChildBodyName);
            if (!Particles.IsValidIndex(ParentParticle) || !Particles.IsValidIndex(ChildParticle) ||
                ParentParticle == ChildParticle)
            {
                continue;
            }

            const uint64 Key = (static_cast<uint64>(ParentParticle + 1) << 32) |
                static_cast<uint32>(ChildParticle + 1);
            const uint64 TypedKey = Key ^ (static_cast<uint64>(SourceLink.m_LinkType.GetValue()) << 56);
            const bool bDuplicateLink = LinkKeys.Contains(TypedKey);

            FLink Link;
            Link.ParentParticleIndex = ParentParticle;
            Link.ChildParticleIndex = ChildParticle;
            Link.LinkType = static_cast<uint8>(SourceLink.m_LinkType.GetValue());
            Link.Stiffness = NormalizeStrength(
                FMath::Max(FMath::Abs(SourceLink.m_LinkStr), FMath::Abs(SourceLink.m_LinkParentStr)), 0.65f);
            Link.Damping = NormalizeStrength(SourceLink.m_LRAdamping, 0.05f);
            Link.bEnableCone = SourceLink.m_EnableCone;
            float ConeLimit = FMath::Max(FMath::Abs(SourceLink.m_LimitY), FMath::Abs(SourceLink.m_LimitZ));
            if (ConeLimit <= KINDA_SMALL_NUMBER)
            {
                ConeLimit = FMath::DegreesToRadians(75.0f);
            }
            else if (ConeLimit > PI)
            {
                ConeLimit = FMath::DegreesToRadians(FMath::Clamp(ConeLimit, 2.0f, 178.0f));
            }
            Link.ConeLimitRadians = FMath::Clamp(
                ConeLimit, FMath::DegreesToRadians(2.0f), FMath::DegreesToRadians(178.0f));
            Link.ConeStiffness = NormalizeStrength(
                FMath::Max(FMath::Abs(SourceLink.m_ConeInnerStr), FMath::Abs(SourceLink.m_ConeOuterStr)), 0.5f);
            Link.PinStrength = NormalizeStrength(SourceLink.m_PinStr, 0.0f);
            Link.PinRadius = FMath::Clamp(FMath::Abs(SourceLink.m_PinRadius), 0.0f, 250.0f);
            Link.bSelfCollision = SourceLink.m_IsSelfCollision;
            if (bDuplicateLink)
            {
                // A Rebirth simple distance link and cone descriptor can share
                // endpoints. Merge cone policy instead of discarding it.
                for (FLink& Existing : Links)
                    if (Existing.ParentParticleIndex == ParentParticle && Existing.ChildParticleIndex == ChildParticle &&
                        Existing.LinkType == Link.LinkType && Link.bEnableCone)
                    {
                        Existing.bEnableCone = true;
                        Existing.ConeLimitRadians = Link.ConeLimitRadians;
                        Existing.ConeStiffness = Link.ConeStiffness;
                        break;
                    }
            }
            else
            {
                LinkKeys.Add(TypedKey);
                Links.Add(Link);
            }

            FParticle& Child = Particles[ChildParticle];
            Child.bSelfCollision = Child.bSelfCollision || SourceLink.m_IsSelfCollision;
            const bool bSkeletonParent = Child.SkeletonParentBoneIndex == Particles[ParentParticle].BoneIndex;
            const bool bPreferred = SourceLink.m_LinkType == ESQEX_Bonamik_LinkType_ParentChild ||
                SourceLink.m_LinkType == ESQEX_Bonamik_LinkType_KdiConstraint || bSkeletonParent;
            if (Child.PrimaryParentParticleIndex == INDEX_NONE || bPreferred)
            {
                Child.PrimaryParentParticleIndex = ParentParticle;
                Child.PrimaryParentBoneIndex = Particles[ParentParticle].BoneIndex;
            }
        }

        for (const FSQEX_BonamikPlaneDesc& SourcePlane : Asset->m_Planes)
        {
            FPlane Plane;
            Plane.ParticleA = ResolveParticle(SourcePlane.m_ParticleA, SourcePlane.m_ParticleAName);
            Plane.ParticleB = ResolveParticle(SourcePlane.m_ParticleB, SourcePlane.m_ParticleBName);
            Plane.ParticleC = ResolveParticle(SourcePlane.m_ParticleC, SourcePlane.m_ParticleCName);
            if (!Particles.IsValidIndex(Plane.ParticleA) || !Particles.IsValidIndex(Plane.ParticleB) ||
                !Particles.IsValidIndex(Plane.ParticleC) || Plane.ParticleA == Plane.ParticleB ||
                Plane.ParticleA == Plane.ParticleC || Plane.ParticleB == Plane.ParticleC)
            {
                continue;
            }
            Plane.Thickness = FMath::Clamp(FMath::Abs(SourcePlane.m_Thickness), 0.0f, 100.0f);
            Plane.Offset = FMath::Clamp(SourcePlane.m_Offset, -100.0f, 100.0f);
            Plane.GroupId = SourcePlane.m_GroupId;
            Plane.bCollision = SourcePlane.m_IsCollision;
            Planes.Add(Plane);
        }

        for (const FSQEX_BonamikShapeMatchingDesc& Shape : Asset->m_ShapeMatchings)
        {
            FShapeRegion Region;
            TSet<int32> UniqueParticles;
            const int32 Count = FMath::Clamp(FMath::Max(Shape.m_TotalParticle, Shape.m_RegionSize), 0, 50);
            for (int32 ShapeIndex = 0; ShapeIndex < Count; ++ShapeIndex)
            {
                const int32 ParticleIndex = ResolveParticle(static_cast<int32>(Shape.m_ParticleIds[ShapeIndex]), FString());
                if (Particles.IsValidIndex(ParticleIndex) && !UniqueParticles.Contains(ParticleIndex))
                {
                    UniqueParticles.Add(ParticleIndex);
                    Region.ParticleIndices.Add(ParticleIndex);
                }
            }
            Region.Stiffness = NormalizeStrength(Shape.m_Stiffness, 0.2f);
            if (Region.ParticleIndices.Num() >= 2)
            {
                ShapeRegions.Add(Region);
            }
        }
    }

    for (int32 ParticleIndex = 0; ParticleIndex < Particles.Num(); ++ParticleIndex)
    {
        FParticle& Particle = Particles[ParticleIndex];
        if (Particle.PrimaryParentBoneIndex == INDEX_NONE)
        {
            Particle.PrimaryParentBoneIndex = Particle.SkeletonParentBoneIndex;
            if (const int32* ParentParticle = ParticleIndexByBoneIndex.Find(Particle.SkeletonParentBoneIndex))
            {
                Particle.PrimaryParentParticleIndex = *ParentParticle;
                const uint64 Key = (static_cast<uint64>(*ParentParticle + 1) << 32) |
                    static_cast<uint32>(ParticleIndex + 1);
                if (!LinkKeys.Contains(Key) && *ParentParticle != ParticleIndex)
                {
                    FLink Link;
                    Link.ParentParticleIndex = *ParentParticle;
                    Link.ChildParticleIndex = ParticleIndex;
                    Links.Add(Link);
                    LinkKeys.Add(Key);
                }
            }
        }
        if (!Particle.bKinematic)
        {
            AffectedBoneIndices.AddUnique(Particle.BoneIndex);
        }
    }
    AffectedBoneIndices.Sort();
    AttachmentOrder.Sort([this](int32 A, int32 B) { return Particles[A].AnchorDepth < Particles[B].AnchorDepth; });

    RuntimeColliders = Colliders;
    RuntimeColliders.RemoveAll([&BoneNames](const FRebirthBonamikPreviewCollider& Collider)
    {
        return !BoneNames.IsValidIndex(Collider.BoneIndex) ||
            (Collider.Geometry.SphereElems.Num() == 0 && Collider.Geometry.SphylElems.Num() == 0 &&
             Collider.Geometry.BoxElems.Num() == 0 && Collider.Geometry.ConvexElems.Num() == 0);
    });

    AuthoredWind = AuthoredWind.GetClampedToMaxSize(10000.0f);
    AuthoredStep = FMath::Clamp(AuthoredStep, 1.0f / 240.0f, 1.0f / 30.0f);
    bReady = AffectedBoneIndices.Num() > 0;
    return bReady;
}

bool FRebirthBonamikPreviewSolver::IsReady() const
{
    return bReady;
}

const TArray<int32>& FRebirthBonamikPreviewSolver::GetAffectedBoneIndices() const
{
    return AffectedBoneIndices;
}

void FRebirthBonamikPreviewSolver::InitializeFromPose(const TArray<FTransform>& AnimatedComponentPose)
{
    for (FParticle& Particle : Particles)
    {
        if (!AnimatedComponentPose.IsValidIndex(Particle.BoneIndex))
        {
            Particle.bInitialized = false;
            continue;
        }
        const FTransform& BoneTransform = AnimatedComponentPose[Particle.BoneIndex];
        const FVector AnimatedLocation = BoneTransform.TransformPositionNoScale(Particle.LocalOffset);
        Particle.SimLocation = AnimatedLocation;
        Particle.PreviousLocation = AnimatedLocation;
        Particle.Velocity = FVector::ZeroVector;
        Particle.LastAnimatedLocation = AnimatedLocation;
        Particle.bInitialized = true;
    }
    for (FLink& Link : Links)
    {
        if (Particles.IsValidIndex(Link.ParentParticleIndex) && Particles.IsValidIndex(Link.ChildParticleIndex))
        {
            Link.RestLength = FMath::Max(0.1f, FVector::Dist(
                Particles[Link.ParentParticleIndex].SimLocation,
                Particles[Link.ChildParticleIndex].SimLocation));
        }
    }
    TimeAccumulator = 0.0f;
}

void FRebirthBonamikPreviewSolver::Evaluate(
    float DeltaTime,
    const TArray<FTransform>& AnimatedComponentPose,
    TArray<FTransform>& InOutComponentPose,
    const FRebirthBonamikPreviewSettings& Settings)
{
    if (!bReady || AnimatedComponentPose.Num() == 0 || InOutComponentPose.Num() != AnimatedComponentPose.Num())
    {
        return;
    }

    if (!FMath::IsFinite(DeltaTime) || DeltaTime < 0.0f ||
        !FMath::IsFinite(Settings.Weight) || !FMath::IsFinite(Settings.SpeedRate) ||
        Settings.GravityOverride.ContainsNaN() || Settings.WindAcceleration.ContainsNaN())
    {
        ResetSimulation();
        return;
    }
    for (const FTransform& Transform : AnimatedComponentPose)
    {
        if (Transform.ContainsNaN() || !Transform.GetRotation().IsNormalized())
        {
            ResetSimulation();
            return;
        }
    }
    TArray<FVector> AnimatedLocations;
    AnimatedLocations.SetNumZeroed(Particles.Num());
    bool bMustReset = false;
    const float TeleportDistance = Settings.TeleportDistance > KINDA_SMALL_NUMBER
        ? Settings.TeleportDistance : AuthoredTeleportDistance;
    for (int32 ParticleIndex = 0; ParticleIndex < Particles.Num(); ++ParticleIndex)
    {
        FParticle& Particle = Particles[ParticleIndex];
        if (!AnimatedComponentPose.IsValidIndex(Particle.BoneIndex))
        {
            ResetSimulation();
            return;
        }
        AnimatedLocations[ParticleIndex] = AnimatedComponentPose[Particle.BoneIndex].TransformPositionNoScale(Particle.LocalOffset);
        if (!Particle.bInitialized || AnimatedLocations[ParticleIndex].ContainsNaN() ||
            (TeleportDistance > KINDA_SMALL_NUMBER &&
             FVector::DistSquared(Particle.LastAnimatedLocation, AnimatedLocations[ParticleIndex]) >
                FMath::Square(TeleportDistance)))
        {
            bMustReset = true;
        }
    }

    if (bMustReset)
    {
        InitializeFromPose(AnimatedComponentPose);
    }

    for (int32 ParticleIndex = 0; ParticleIndex < Particles.Num(); ++ParticleIndex)
    {
        FParticle& Particle = Particles[ParticleIndex];
        Particle.LastAnimatedLocation = AnimatedLocations[ParticleIndex];
        if (Particle.bKinematic)
        {
            Particle.SimLocation = AnimatedLocations[ParticleIndex];
            Particle.PreviousLocation = Particle.SimLocation;
            Particle.Velocity = FVector::ZeroVector;
        }
    }
    for (FLink& Link : Links)
    {
        if (!Particles.IsValidIndex(Link.ParentParticleIndex) || !Particles.IsValidIndex(Link.ChildParticleIndex))
        {
            continue;
        }
        const float AnimatedLength = FMath::Max(0.1f, FVector::Dist(
            AnimatedLocations[Link.ParentParticleIndex], AnimatedLocations[Link.ChildParticleIndex]));
        Link.RestLength = Link.RestLength <= KINDA_SMALL_NUMBER
            ? AnimatedLength : FMath::Lerp(Link.RestLength, AnimatedLength, 0.02f);
    }

    const float SpeedRate = FMath::Max(0.0f, Settings.SpeedRate);
    const float SafeDelta = FMath::Clamp(DeltaTime * SpeedRate, 0.0f, 0.25f);
    const float FixedStep = FMath::Clamp(
        AuthoredStep / static_cast<float>(FMath::Max(AuthoredSubsteps, 1)), 1.0f / 480.0f, 1.0f / 30.0f);
    const int32 MaxSubsteps = FMath::Clamp(Settings.MaxSubsteps, 1, 16);
    TimeAccumulator = FMath::Min(TimeAccumulator + SafeDelta, FixedStep * static_cast<float>(MaxSubsteps));
    const FVector Gravity = Settings.bOverrideGravity ? Settings.GravityOverride : AuthoredGravity;
    const FVector Wind = AuthoredWind + Settings.WindAcceleration;
    const int32 Iterations = FMath::Clamp(
        FMath::Max(AuthoredConstraintIterations, Settings.MaxConstraintIterations), 1, 24);

    int32 StepCount = 0;
    while (TimeAccumulator + SMALL_NUMBER >= FixedStep && StepCount < MaxSubsteps)
    {
        SimulateStep(FixedStep, AnimatedComponentPose, AnimatedLocations, Settings, Gravity, Wind, Iterations);
        TimeAccumulator -= FixedStep;
        ++StepCount;
    }

    const float Weight = FMath::Clamp(Settings.Weight, 0.0f, 1.0f);
    for (const int32 BoneIndex : AffectedBoneIndices)
    {
        const int32* ParticleIndexPtr = ParticleIndexByBoneIndex.Find(BoneIndex);
        if (!ParticleIndexPtr || !Particles.IsValidIndex(*ParticleIndexPtr) ||
            !AnimatedComponentPose.IsValidIndex(BoneIndex))
        {
            continue;
        }

        const FParticle& Particle = Particles[*ParticleIndexPtr];
        FTransform SimulatedTransform = AnimatedComponentPose[BoneIndex];

        FVector AnimatedParentLocation = AnimatedLocations[*ParticleIndexPtr];
        FVector SimulatedParentLocation = Particle.SimLocation;
        if (Particles.IsValidIndex(Particle.PrimaryParentParticleIndex))
        {
            AnimatedParentLocation = AnimatedLocations[Particle.PrimaryParentParticleIndex];
            SimulatedParentLocation = Particles[Particle.PrimaryParentParticleIndex].SimLocation;
        }
        else if (AnimatedComponentPose.IsValidIndex(Particle.PrimaryParentBoneIndex))
        {
            AnimatedParentLocation = AnimatedComponentPose[Particle.PrimaryParentBoneIndex].GetLocation();
            SimulatedParentLocation = InOutComponentPose[Particle.PrimaryParentBoneIndex].GetLocation();
        }

        const FVector AnimatedDirection = (AnimatedLocations[*ParticleIndexPtr] - AnimatedParentLocation).GetSafeNormal();
        const FVector SimulatedDirection = (Particle.SimLocation - SimulatedParentLocation).GetSafeNormal();
        if (!AnimatedDirection.IsNearlyZero() && !SimulatedDirection.IsNearlyZero())
        {
            const FQuat TargetRotation = FQuat::FindBetweenNormals(AnimatedDirection, SimulatedDirection) *
                AnimatedComponentPose[BoneIndex].GetRotation();
            SimulatedTransform.SetRotation(FQuat::Slerp(
                AnimatedComponentPose[BoneIndex].GetRotation(), TargetRotation, Weight));
        }
        SimulatedTransform.NormalizeRotation();
        // Convert the authored body center back to the bone origin using the
        // final rotated offset, rather than the unsimulated bone orientation.
        const FVector SimulatedJointLocation = Particle.SimLocation -
            SimulatedTransform.TransformVectorNoScale(Particle.LocalOffset);
        SimulatedTransform.SetLocation(FMath::Lerp(
            AnimatedComponentPose[BoneIndex].GetLocation(), SimulatedJointLocation, Weight));
        if (!SimulatedTransform.ContainsNaN())
        {
            InOutComponentPose[BoneIndex] = SimulatedTransform;
        }
    }
}

void FRebirthBonamikPreviewSolver::UpdateBodyAttachments(
    const TArray<FTransform>& AnimatedComponentPose, const TArray<FVector>& AnimatedLocations)
{
    BodyRotations.SetNum(Particles.Num());
    for (int32 Index = 0; Index < Particles.Num(); ++Index)
    {
        const FParticle& Particle = Particles[Index];
        FQuat Rotation = AnimatedComponentPose[Particle.BoneIndex].GetRotation();
        if (!Particle.bKinematic)
        {
            FVector AnimatedParent = AnimatedLocations[Index];
            FVector SimulatedParent = Particle.SimLocation;
            if (Particles.IsValidIndex(Particle.PrimaryParentParticleIndex))
            {
                AnimatedParent = AnimatedLocations[Particle.PrimaryParentParticleIndex];
                SimulatedParent = Particles[Particle.PrimaryParentParticleIndex].SimLocation;
            }
            else if (AnimatedComponentPose.IsValidIndex(Particle.PrimaryParentBoneIndex))
            {
                AnimatedParent = AnimatedComponentPose[Particle.PrimaryParentBoneIndex].GetLocation();
                SimulatedParent = AnimatedParent;
            }
            const FVector From = (AnimatedLocations[Index] - AnimatedParent).GetSafeNormal();
            const FVector To = (Particle.SimLocation - SimulatedParent).GetSafeNormal();
            if (!From.IsNearlyZero() && !To.IsNearlyZero()) Rotation = FQuat::FindBetweenNormals(From, To) * Rotation;
        }
        BodyRotations[Index] = (Rotation * Particle.LocalRotation).GetNormalized();
    }
    for (int32 Index : AttachmentOrder)
    {
        FParticle& Child = Particles[Index];
        const int32 ParentIndex = Child.AnchorParentParticleIndex;
        if (!Particles.IsValidIndex(ParentIndex)) continue;
        const FTransform ParentFrame(BodyRotations[ParentIndex], Particles[ParentIndex].SimLocation, FVector::OneVector);
        const FTransform ChildFrame = Child.AnchorLocalTransform * ParentFrame;
        if (ChildFrame.ContainsNaN()) continue;
        Child.SimLocation = ChildFrame.GetTranslation();
        Child.Velocity = FVector::ZeroVector;
        BodyRotations[Index] = ChildFrame.GetRotation().GetNormalized();
    }
}

void FRebirthBonamikPreviewSolver::SolveAuthoredCollisions()
{
    TArray<FVector> Positions;
    TArray<float> Radii, InverseMasses;
    Positions.Reserve(Particles.Num()); Radii.Reserve(Particles.Num()); InverseMasses.Reserve(Particles.Num());
    for (const FParticle& Particle : Particles)
    {
        Positions.Add(Particle.SimLocation);
        Radii.Add(Particle.AuthoredRadius);
        InverseMasses.Add(Particle.bKinematic ? 0.0f : Particle.InverseMass);
    }
    AuthoredCollision.Solve(Positions, Radii, InverseMasses, BodyRotations);
    for (int32 Index = 0; Index < Particles.Num(); ++Index)
        if (!Particles[Index].bKinematic && !Positions[Index].ContainsNaN()) Particles[Index].SimLocation = Positions[Index];
}

void FRebirthBonamikPreviewSolver::SimulateStep(
    float StepSeconds,
    const TArray<FTransform>& AnimatedComponentPose,
    const TArray<FVector>& AnimatedLocations,
    const FRebirthBonamikPreviewSettings& Settings,
    const FVector& Gravity,
    const FVector& Wind,
    int32 ConstraintIterations)
{
    for (int32 ParticleIndex = 0; ParticleIndex < Particles.Num(); ++ParticleIndex)
    {
        FParticle& Particle = Particles[ParticleIndex];
        Particle.PreviousLocation = Particle.SimLocation;
        if (Particle.bKinematic)
        {
            Particle.SimLocation = AnimatedLocations[ParticleIndex];
            Particle.Velocity = FVector::ZeroVector;
            continue;
        }

        const FVector TargetAcceleration = (AnimatedLocations[ParticleIndex] - Particle.SimLocation) * Particle.Stiffness;
        const FVector ExternalAcceleration = Gravity + Wind * Particle.WindDrag;
        Particle.Velocity += (TargetAcceleration + ExternalAcceleration - Particle.Velocity * Particle.Damping) * StepSeconds;
        Particle.Velocity = Particle.Velocity.GetClampedToMaxSize(10000.0f);
        Particle.SimLocation += Particle.Velocity * StepSeconds;
        SanitizeParticle(Particle, AnimatedLocations[ParticleIndex]);
    }

    for (int32 Iteration = 0; Iteration < ConstraintIterations; ++Iteration)
    {
        UpdateBodyAttachments(AnimatedComponentPose, AnimatedLocations);
        SolveLinks(AnimatedLocations);
        UpdateBodyAttachments(AnimatedComponentPose, AnimatedLocations);
        SolvePlanes(AnimatedLocations);
        SolveShapeMatching(AnimatedLocations);
        SolveDisplacementAndCollisions(AnimatedComponentPose, AnimatedLocations, Settings);
        SolveSelfCollision();
        if (Settings.bEnableCollisions) SolveAuthoredCollisions();
    }
    UpdateBodyAttachments(AnimatedComponentPose, AnimatedLocations);

    for (int32 ParticleIndex = 0; ParticleIndex < Particles.Num(); ++ParticleIndex)
    {
        FParticle& Particle = Particles[ParticleIndex];
        Particle.Velocity = Particle.bKinematic
            ? FVector::ZeroVector
            : (Particle.SimLocation - Particle.PreviousLocation) / FMath::Max(StepSeconds, SMALL_NUMBER);
        Particle.Velocity = Particle.Velocity.GetClampedToMaxSize(10000.0f);
        SanitizeParticle(Particle, AnimatedLocations[ParticleIndex]);
    }
}

void FRebirthBonamikPreviewSolver::SolveLinks(const TArray<FVector>& AnimatedLocations)
{
    for (const FLink& Link : Links)
    {
        if (!Particles.IsValidIndex(Link.ParentParticleIndex) || !Particles.IsValidIndex(Link.ChildParticleIndex))
        {
            continue;
        }
        FParticle& Parent = Particles[Link.ParentParticleIndex];
        FParticle& Child = Particles[Link.ChildParticleIndex];

        FVector Delta = Child.SimLocation - Parent.SimLocation;
        const float Distance = Delta.Size();
        if (Distance > KINDA_SMALL_NUMBER && Link.RestLength > KINDA_SMALL_NUMBER)
        {
            const FVector Correction = Delta * ((Distance - Link.RestLength) / Distance) * Link.Stiffness;
            const float ParentWeight = Parent.bKinematic ? 0.0f : Parent.InverseMass;
            const float ChildWeight = Child.bKinematic ? 0.0f : Child.InverseMass;
            const float TotalWeight = ParentWeight + ChildWeight;
            if (TotalWeight > KINDA_SMALL_NUMBER)
            {
                Parent.SimLocation += Correction * (ParentWeight / TotalWeight);
                Child.SimLocation -= Correction * (ChildWeight / TotalWeight);
            }
        }

        if (Link.bEnableCone && !Child.bKinematic)
        {
            const FVector AnimatedDirection = (AnimatedLocations[Link.ChildParticleIndex] -
                AnimatedLocations[Link.ParentParticleIndex]).GetSafeNormal();
            FVector SimulatedDirection = (Child.SimLocation - Parent.SimLocation).GetSafeNormal();
            if (!AnimatedDirection.IsNearlyZero() && !SimulatedDirection.IsNearlyZero())
            {
                const float Angle = FMath::Acos(FMath::Clamp(
                    FVector::DotProduct(AnimatedDirection, SimulatedDirection), -1.0f, 1.0f));
                if (Angle > Link.ConeLimitRadians)
                {
                    const float Excess = (Angle - Link.ConeLimitRadians) / FMath::Max(Angle, KINDA_SMALL_NUMBER);
                    SimulatedDirection = FMath::Lerp(
                        SimulatedDirection, AnimatedDirection, Excess * Link.ConeStiffness).GetSafeNormal();
                    Child.SimLocation = Parent.SimLocation + SimulatedDirection * Link.RestLength;
                }
            }
        }

        const bool bPinLink = Link.LinkType == static_cast<uint8>(ESQEX_Bonamik_LinkType_PinConstraint);
        if ((bPinLink || Link.PinStrength > KINDA_SMALL_NUMBER) && !Child.bKinematic)
        {
            const float PinStrength = bPinLink ? FMath::Max(Link.PinStrength, 0.65f) : Link.PinStrength;
            FVector Offset = Child.SimLocation - AnimatedLocations[Link.ChildParticleIndex];
            if (Link.PinRadius > KINDA_SMALL_NUMBER && Offset.Size() > Link.PinRadius)
            {
                Offset = Offset.GetClampedToMaxSize(Link.PinRadius);
            }
            const FVector PinTarget = Link.PinRadius > KINDA_SMALL_NUMBER
                ? AnimatedLocations[Link.ChildParticleIndex] + Offset
                : AnimatedLocations[Link.ChildParticleIndex];
            Child.SimLocation = FMath::Lerp(Child.SimLocation, PinTarget, PinStrength);
        }

        if (Link.Damping > KINDA_SMALL_NUMBER)
        {
            const FVector RelativeVelocity = Child.Velocity - Parent.Velocity;
            Child.Velocity -= RelativeVelocity * Link.Damping * 0.5f;
            if (!Parent.bKinematic)
            {
                Parent.Velocity += RelativeVelocity * Link.Damping * 0.5f;
            }
        }
    }
}

void FRebirthBonamikPreviewSolver::SolvePlanes(const TArray<FVector>& AnimatedLocations)
{
    for (const FPlane& Plane : Planes)
    {
        if (!Particles.IsValidIndex(Plane.ParticleA) || !Particles.IsValidIndex(Plane.ParticleB) ||
            !Particles.IsValidIndex(Plane.ParticleC))
        {
            continue;
        }
        const int32 Indices[3] = { Plane.ParticleA, Plane.ParticleB, Plane.ParticleC };
        const FVector SimulatedCentroid = (Particles[Indices[0]].SimLocation +
            Particles[Indices[1]].SimLocation + Particles[Indices[2]].SimLocation) / 3.0f;
        const FVector AnimatedCentroid = (AnimatedLocations[Indices[0]] +
            AnimatedLocations[Indices[1]] + AnimatedLocations[Indices[2]]) / 3.0f;
        for (int32 PlaneParticle = 0; PlaneParticle < 3; ++PlaneParticle)
        {
            FParticle& Particle = Particles[Indices[PlaneParticle]];
            if (!Particle.bKinematic)
            {
                const FVector Target = SimulatedCentroid +
                    (AnimatedLocations[Indices[PlaneParticle]] - AnimatedCentroid);
                Particle.SimLocation = FMath::Lerp(Particle.SimLocation, Target, Plane.Stiffness);
            }
        }

        if (Plane.bCollision)
        {
            const FVector A = Particles[Plane.ParticleA].SimLocation;
            const FVector B = Particles[Plane.ParticleB].SimLocation;
            const FVector C = Particles[Plane.ParticleC].SimLocation;
            const FVector Normal = FVector::CrossProduct(B - A, C - A).GetSafeNormal();
            if (!Normal.IsNearlyZero())
            {
                for (FParticle& Particle : Particles)
                {
                    if (Particle.bKinematic || Particle.GroupId != Plane.GroupId)
                    {
                        continue;
                    }
                    const float SignedDistance = FVector::DotProduct(Particle.SimLocation - A, Normal) - Plane.Offset;
                    const float MinimumDistance = Plane.Thickness + Particle.CollisionRadius;
                    if (SignedDistance < MinimumDistance)
                    {
                        Particle.SimLocation += Normal * (MinimumDistance - SignedDistance);
                    }
                }
            }
        }
    }
}

void FRebirthBonamikPreviewSolver::SolveShapeMatching(const TArray<FVector>& AnimatedLocations)
{
    for (const FShapeRegion& Region : ShapeRegions)
    {
        FVector SimulatedCentroid = FVector::ZeroVector;
        FVector AnimatedCentroid = FVector::ZeroVector;
        int32 ValidCount = 0;
        for (const int32 ParticleIndex : Region.ParticleIndices)
        {
            if (Particles.IsValidIndex(ParticleIndex))
            {
                SimulatedCentroid += Particles[ParticleIndex].SimLocation;
                AnimatedCentroid += AnimatedLocations[ParticleIndex];
                ++ValidCount;
            }
        }
        if (ValidCount < 2)
        {
            continue;
        }
        SimulatedCentroid /= static_cast<float>(ValidCount);
        AnimatedCentroid /= static_cast<float>(ValidCount);
        for (const int32 ParticleIndex : Region.ParticleIndices)
        {
            if (Particles.IsValidIndex(ParticleIndex) && !Particles[ParticleIndex].bKinematic)
            {
                const FVector Target = SimulatedCentroid + (AnimatedLocations[ParticleIndex] - AnimatedCentroid);
                Particles[ParticleIndex].SimLocation = FMath::Lerp(
                    Particles[ParticleIndex].SimLocation, Target, Region.Stiffness);
            }
        }
    }
}

void FRebirthBonamikPreviewSolver::SolveDisplacementAndCollisions(
    const TArray<FTransform>& AnimatedComponentPose,
    const TArray<FVector>& AnimatedLocations,
    const FRebirthBonamikPreviewSettings& Settings)
{
    for (int32 ParticleIndex = 0; ParticleIndex < Particles.Num(); ++ParticleIndex)
    {
        FParticle& Particle = Particles[ParticleIndex];
        if (Particle.bKinematic)
        {
            continue;
        }

        const float ConstraintRadius = Particle.AdditionalConstraintRadius > KINDA_SMALL_NUMBER &&
            Particle.bSpringConstraint ? Particle.AdditionalConstraintRadius : Particle.MaxDisplacement;
        FVector Displacement = Particle.SimLocation - AnimatedLocations[ParticleIndex];
        if (Displacement.SizeSquared() > FMath::Square(ConstraintRadius))
        {
            Particle.SimLocation = AnimatedLocations[ParticleIndex] +
                Displacement.GetSafeNormal() * ConstraintRadius;
        }

        if (Settings.bEnableGroundCollision &&
            Particle.SimLocation.Z - Particle.CollisionRadius < Settings.GroundHeight)
        {
            Particle.SimLocation.Z = Settings.GroundHeight + Particle.CollisionRadius;
            if (Particle.Velocity.Z < 0.0f)
            {
                Particle.Velocity.Z = -Particle.Velocity.Z * Particle.Restitution;
            }
            Particle.Velocity.X *= 1.0f - Particle.Friction;
            Particle.Velocity.Y *= 1.0f - Particle.Friction;
        }

        if (!Settings.bEnableCollisions || !Particle.bCollisionEnabled)
        {
            continue;
        }
        for (const FRebirthBonamikPreviewCollider& Collider : RuntimeColliders)
        {
            if (!AnimatedComponentPose.IsValidIndex(Collider.BoneIndex) ||
                Collider.BoneIndex == Particle.BoneIndex || Collider.BoneIndex == Particle.PrimaryParentBoneIndex)
            {
                continue;
            }
            FVector Normal = FVector::ZeroVector;
            if (ResolveAggregateCollision(
                    Collider.Geometry, AnimatedComponentPose[Collider.BoneIndex], Particle.CollisionRadius,
                    Particle.SimLocation, Normal))
            {
                const float NormalSpeed = FVector::DotProduct(Particle.Velocity, Normal);
                if (NormalSpeed < 0.0f)
                {
                    Particle.Velocity -= Normal * NormalSpeed * (1.0f + Particle.Restitution);
                }
                const FVector NormalVelocity = Normal * FVector::DotProduct(Particle.Velocity, Normal);
                Particle.Velocity = NormalVelocity +
                    (Particle.Velocity - NormalVelocity) * (1.0f - Particle.Friction);
            }
        }
    }
}

void FRebirthBonamikPreviewSolver::SolveSelfCollision()
{
    for (int32 ParticleAIndex = 0; ParticleAIndex < Particles.Num(); ++ParticleAIndex)
    {
        FParticle& A = Particles[ParticleAIndex];
        if (!A.bSelfCollision || A.bKinematic)
        {
            continue;
        }
        for (int32 ParticleBIndex = ParticleAIndex + 1; ParticleBIndex < Particles.Num(); ++ParticleBIndex)
        {
            FParticle& B = Particles[ParticleBIndex];
            if (!B.bSelfCollision || A.GroupId != B.GroupId ||
                A.PrimaryParentParticleIndex == ParticleBIndex || B.PrimaryParentParticleIndex == ParticleAIndex)
            {
                continue;
            }
            FVector Delta = B.SimLocation - A.SimLocation;
            const float MinimumDistance = A.CollisionRadius + B.CollisionRadius;
            const float Distance = Delta.Size();
            if (Distance >= MinimumDistance)
            {
                continue;
            }
            if (!Delta.Normalize())
            {
                Delta = FVector::UpVector;
            }
            const FVector Correction = Delta * (MinimumDistance - Distance);
            const float AWeight = A.bKinematic ? 0.0f : A.InverseMass;
            const float BWeight = B.bKinematic ? 0.0f : B.InverseMass;
            const float TotalWeight = AWeight + BWeight;
            if (TotalWeight > KINDA_SMALL_NUMBER)
            {
                A.SimLocation -= Correction * (AWeight / TotalWeight);
                B.SimLocation += Correction * (BWeight / TotalWeight);
            }
        }
    }
}

void FRebirthBonamikPreviewSolver::SanitizeParticle(FParticle& Particle, const FVector& AnimatedLocation)
{
    if (Particle.SimLocation.ContainsNaN() || Particle.Velocity.ContainsNaN() ||
        FVector::DistSquared(Particle.SimLocation, AnimatedLocation) > FMath::Square(100000.0f))
    {
        Particle.SimLocation = AnimatedLocation;
        Particle.PreviousLocation = AnimatedLocation;
        Particle.Velocity = FVector::ZeroVector;
        Particle.bInitialized = true;
    }
}
