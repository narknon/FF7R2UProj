#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/AggregateGeom.h"
#include "RebirthBonamikAuthoredCollision.h"

#include "SQEX_BonamikAsset.h"

// Value snapshot only. The proprietary runtime is unavailable; this is the
// prior Tres custom Bonamik-data preview, with approximate constraint math.
struct FRebirthBonamikPreviewData
{
    FSQEX_BonamikSceneManagerDesc m_SceneManager;
    TArray<FSQEX_BonamikSolverDesc> m_Solvers;
    TArray<FSQEX_BonamikBodyDesc> m_Bodies;
    TArray<FSQEX_BonamikLinkDesc> m_Links;
    TArray<FSQEX_BonamikPlaneDesc> m_Planes;
    TArray<FSQEX_BonamikShapeMatchingDesc> m_ShapeMatchings;
    TArray<FTransform> SourceBodyLocalTransforms;
    TArray<int32> BodyAnchorDepths;
    bool bSceneVectorsAreUECentimeters = false;
    TArray<FSQEX_BonamikShapeDesc> AuthoredShapes;
    TArray<FSQEX_BonamikCollisionCliqueDesc> AuthoredCliques;
    float m_TeleportDistance = 100.0f;
};

struct  FRebirthBonamikPreviewCollider
{
    int32 BoneIndex;
    FKAggregateGeom Geometry;

    FRebirthBonamikPreviewCollider()
        : BoneIndex(INDEX_NONE)
    {
    }
};

struct  FRebirthBonamikPreviewSettings
{
    FVector WindAcceleration;
    FVector GravityOverride;
    float Weight;
    float SpeedRate;
    float TeleportDistance;
    float GroundHeight;
    int32 MaxSubsteps;
    int32 MaxConstraintIterations;
    bool bOverrideGravity;
    bool bEnableCollisions;
    bool bEnableGroundCollision;

    FRebirthBonamikPreviewSettings()
        : WindAcceleration(FVector::ZeroVector)
        , GravityOverride(0.0f, 0.0f, -980.0f)
        , Weight(1.0f)
        , SpeedRate(1.0f)
        , TeleportDistance(0.0f)
        , GroundHeight(0.0f)
        , MaxSubsteps(8)
        , MaxConstraintIterations(12)
        , bOverrideGravity(false)
        , bEnableCollisions(true)
        , bEnableGroundCollision(false)
    {
    }
};

// Staged private custom preview core; not Square Enix solver/runtime parity.
class  FRebirthBonamikPreviewSolver
{
public:
    FRebirthBonamikPreviewSolver();

    void Reset();
    void ResetSimulation();

    bool Rebuild(
        const TArray<FRebirthBonamikPreviewData>& Assets,
        const TArray<FName>& BoneNames,
        const TArray<int32>& ParentBoneIndices,
        const TArray<FRebirthBonamikPreviewCollider>& Colliders);

    bool IsReady() const;
    const TArray<int32>& GetAffectedBoneIndices() const;
    int32 GetAuthoredShapeCount() const { return AuthoredCollision.GetShapeCount(); }
    int32 GetAuthoredCollisionPairCount() const { return AuthoredCollision.GetPairCount(); }
    int32 GetParticleCount() const { return Particles.Num(); }
    int32 GetAttachmentCount() const { return AttachmentOrder.Num(); }

    void Evaluate(
        float DeltaTime,
        const TArray<FTransform>& AnimatedComponentPose,
        TArray<FTransform>& InOutComponentPose,
        const FRebirthBonamikPreviewSettings& Settings);

private:
    struct FParticle
    {
        int32 BoneIndex;
        int32 SkeletonParentBoneIndex;
        int32 PrimaryParentBoneIndex;
        int32 PrimaryParentParticleIndex;
        FVector SimLocation;
        FVector PreviousLocation;
        FVector Velocity;
        FVector LastAnimatedLocation;
        FVector LocalOffset;
        FQuat LocalRotation = FQuat::Identity;
        FTransform AnchorLocalTransform = FTransform::Identity;
        int32 AnchorParentParticleIndex = INDEX_NONE;
        int32 AnchorDepth = 0;
        float AuthoredRadius = 0.0f;
        float Stiffness;
        float Damping;
        float MaxDisplacement;
        float CollisionRadius;
        float InverseMass;
        float Friction;
        float Restitution;
        float WindDrag;
        float AdditionalConstraintRadius;
        uint32 GroupId;
        int32 SourceCount;
        bool bCollisionEnabled;
        bool bSelfCollision;
        bool bSpringConstraint;
        bool bKinematic;
        bool bInitialized;

        FParticle();
    };

    struct FLink
    {
        int32 ParentParticleIndex;
        int32 ChildParticleIndex;
        float RestLength;
        float Stiffness;
        float Damping;
        float ConeLimitRadians;
        float ConeStiffness;
        float PinStrength;
        float PinRadius;
        uint8 LinkType;
        bool bEnableCone;
        bool bSelfCollision;

        FLink();
    };

    struct FPlane
    {
        int32 ParticleA;
        int32 ParticleB;
        int32 ParticleC;
        float Stiffness;
        float Thickness;
        float Offset;
        uint32 GroupId;
        bool bCollision;

        FPlane();
    };

    struct FShapeRegion
    {
        TArray<int32> ParticleIndices;
        float Stiffness;

        FShapeRegion()
            : Stiffness(0.2f)
        {
        }
    };

    void InitializeFromPose(const TArray<FTransform>& AnimatedComponentPose);
    void UpdateBodyAttachments(const TArray<FTransform>& AnimatedComponentPose, const TArray<FVector>& AnimatedLocations);
    void SolveAuthoredCollisions();
    void SimulateStep(
        float StepSeconds,
        const TArray<FTransform>& AnimatedComponentPose,
        const TArray<FVector>& AnimatedLocations,
        const FRebirthBonamikPreviewSettings& Settings,
        const FVector& Gravity,
        const FVector& Wind,
        int32 ConstraintIterations);
    void SolveLinks(const TArray<FVector>& AnimatedLocations);
    void SolvePlanes(const TArray<FVector>& AnimatedLocations);
    void SolveShapeMatching(const TArray<FVector>& AnimatedLocations);
    void SolveDisplacementAndCollisions(
        const TArray<FTransform>& AnimatedComponentPose,
        const TArray<FVector>& AnimatedLocations,
        const FRebirthBonamikPreviewSettings& Settings);
    void SolveSelfCollision();
    void SanitizeParticle(FParticle& Particle, const FVector& AnimatedLocation);

    TArray<FParticle> Particles;
    TArray<FLink> Links;
    TArray<FPlane> Planes;
    TArray<FShapeRegion> ShapeRegions;
    TArray<FRebirthBonamikPreviewCollider> RuntimeColliders;
    FRebirthBonamikAuthoredCollision AuthoredCollision;
    TArray<int32> AttachmentOrder;
    TArray<FQuat> BodyRotations;
    TArray<int32> AffectedBoneIndices;
    TMap<int32, int32> ParticleIndexByBoneIndex;
    FVector AuthoredGravity;
    FVector AuthoredWind;
    float AuthoredStep;
    float AuthoredTeleportDistance;
    float TimeAccumulator;
    int32 AuthoredSubsteps;
    int32 AuthoredConstraintIterations;
    bool bReady;
};
