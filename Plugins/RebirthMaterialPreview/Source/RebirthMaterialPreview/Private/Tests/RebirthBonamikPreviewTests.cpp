#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "Components/PoseableMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "RebirthBonamikPreviewSession.h"
#include "RebirthBonamikAuthoredCollision.h"
#include "UObject/StrongObjectPtr.h"
#include "UObject/UObjectGlobals.h"
#include <limits>

namespace
{
    TArray<FTransform> BonamikTestComponentPose(const TArray<FTransform>& Local, const FReferenceSkeleton& Ref)
    {
        TArray<FTransform> Result = Local;
        for (int32 Index = 0; Index < Result.Num(); ++Index)
        {
            const int32 Parent = Ref.GetParentIndex(Index);
            if (Parent != INDEX_NONE) Result[Index] = Result[Index] * Result[Parent];
        }
        return Result;
    }
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRebirthBonamikPreviewFixtureTest,
    "Rebirth.Preview.Bonamik.StandardSephirothOwnershipReset",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRebirthBonamikPreviewFixtureTest::RunTest(const FString& Parameters)
{
    // Separate small collision oracles verify direction and full sample-radius
    // clearance. The genuine fixture below remains the ownership/motion oracle.
    int32 CollisionOracleCases = 0;
    for (bool bCapsule : { false, true })
    {
        for (bool bInverse : { false, true })
        {
            FSQEX_BonamikShapeDesc Receiver;
            Receiver.mShapeId = 0;
            Receiver.mType = TEXT("sphere");
            Receiver.mBodies.Add(TEXT("receiver"));
            Receiver.mReceiverGroups.Add(TEXT("oracle"));
            FSQEX_BonamikShapeDesc Collider;
            Collider.mShapeId = 1;
            Collider.mType = bCapsule ? TEXT("capsule") : TEXT("sphere");
            Collider.mBodies.Add(TEXT("anchorA"));
            if (bCapsule) Collider.mBodies.Add(TEXT("anchorB"));
            Collider.mRepulsorGroups.Add(TEXT("oracle"));
            Collider.bIsInverse = bInverse;
            Collider.bIsInfinity = bInverse; // Retain the genuine authored flag.
            TArray<FSQEX_BonamikShapeDesc> Shapes = { Receiver, Collider };
            TMap<FName, int32> BodyMap;
            BodyMap.Add(TEXT("receiver"), 0);
            BodyMap.Add(TEXT("anchorA"), 1);
            BodyMap.Add(TEXT("anchorB"), 2);
            FRebirthBonamikAuthoredCollision Collision;
            if (!TestTrue(TEXT("Normal and inverse authored primitives are accepted"),
                Collision.AddAsset(Shapes, TArray<FSQEX_BonamikCollisionCliqueDesc>(), BodyMap))) return false;
            const TArray<float> Radii = { 1.0f, 5.0f, 5.0f };
            const TArray<float> InverseMasses = { 1.0f, 0.0f, 0.0f };
            const TArray<FQuat> Rotations = { FQuat::Identity, FQuat::Identity, FQuat::Identity };
            for (float InitialX : { 3.0f, 8.0f })
            {
                TArray<FVector> Positions = { FVector(InitialX, 0.0f, 0.0f),
                    FVector(0.0f, bCapsule ? -2.0f : 0.0f, 0.0f), FVector(0.0f, 2.0f, 0.0f) };
                const TArray<FVector> Before = Positions;
                Collision.Solve(Positions, Radii, InverseMasses, Rotations);
                const float ExpectedX = bInverse ? FMath::Min(InitialX, 4.0f) : FMath::Max(InitialX, 6.0f);
                TestTrue(TEXT("Sphere/capsule correction matches exclusion or full-radius containment"),
                    Positions[0].Equals(FVector(ExpectedX, 0.0f, 0.0f), 0.001f));
                TestTrue(TEXT("Collision preserves both kinematic collider anchors"),
                    Positions[1].Equals(Before[1], 0.001f) && Positions[2].Equals(Before[2], 0.001f));
                const FTransform Frame(FRotator(0.0f, 90.0f, 0.0f), FVector(100.0f, -50.0f, 20.0f), FVector::OneVector);
                const TArray<FVector> ExpectedPositions = Positions;
                for (int32 Point = 0; Point < Positions.Num(); ++Point) Positions[Point] = Frame.TransformPosition(Before[Point]);
                const TArray<FQuat> WorldRotations = { Frame.GetRotation(), Frame.GetRotation(), Frame.GetRotation() };
                Collision.Solve(Positions, Radii, InverseMasses, WorldRotations);
                for (int32 Point = 0; Point < Positions.Num(); ++Point)
                    TestTrue(TEXT("Normal/inverse primitive correction follows translated yaw frame"),
                        Positions[Point].Equals(Frame.TransformPosition(ExpectedPositions[Point]), 0.001f));
                ++CollisionOracleCases;
            }
            if (bCapsule)
            {
                TArray<FVector> Positions = { FVector(0.0f, 10.0f, 0.0f), FVector(0.0f, -2.0f, 0.0f), FVector(0.0f, 2.0f, 0.0f) };
                Collision.Solve(Positions, Radii, InverseMasses, Rotations);
                TestTrue(TEXT("Inverse capsule constrains its spherical end cap; normal outside stays unchanged"),
                    Positions[0].Equals(FVector(0.0f, bInverse ? 6.0f : 10.0f, 0.0f), 0.001f));
                ++CollisionOracleCases;
            }
        }
    }
    TestEqual(TEXT("All normal/inverse sphere/capsule oracle cases ran"), CollisionOracleCases, 10);
    AddInfo(FString::Printf(TEXT("BonamikNativeCollision normal_inverse_oracle_cases=%d containment_inferred=true"), CollisionOracleCases));

    // Opt-in editor test only. The test reads the original approved fixture;
    // the target component and all simulation data are transient.
    USkeletalMesh* Mesh = LoadObject<USkeletalMesh>(nullptr,
        TEXT("/Game/Character/Player/PC0010_00_Sephiroth_Standard/Model/PC0010_00.PC0010_00"));
    if (!TestNotNull(TEXT("Genuine Sephiroth mesh loaded"), Mesh)) return false;
    TArray<USQEX_BonamikAsset*> Assets;
    FRebirthBonamikPreviewSession::FindLoadedAssets(Mesh, Assets);
    if (!TestEqual(TEXT("Exactly one attached Bonamik data asset"), Assets.Num(), 1)) return false;
    TStrongObjectPtr<UPoseableMeshComponent> Target(NewObject<UPoseableMeshComponent>(GetTransientPackage(), NAME_None, RF_Transient));
    Target->SetSkeletalMesh(Mesh);
    FRebirthBonamikPreviewSession Session;
    FString Status;
    if (!TestTrue(TEXT("Real BNM produces mapped unique dynamic bone owners"), Session.Initialize(Target.Get(), Assets[0], Status)))
    {
        AddError(Status);
        return false;
    }
    TestEqual(TEXT("All distinct authored bodies retained"), Session.GetBodyCount(), 434);
    TestEqual(TEXT("Only exact authored body-parent links become attachments"), Session.GetAttachmentCount(), 20);
    TestEqual(TEXT("All authored primitive descriptors retained"), Session.GetAuthoredShapeCount(), 624);
    TestEqual(TEXT("Only exact groups and explicit clique pairs allowed"), Session.GetAuthoredCollisionPairCount(), 16964);
    const TArray<FTransform> BasePose = Session.GetReferenceComponentPose();
    for (int32 Index = 0; Index < 120; ++Index)
        if (!TestTrue(TEXT("Bounded two-second simulation stays valid"), Session.TickAndApply(1.0f / 60.0f, BasePose))) return false;
    const TArray<FTransform> FirstRun = Target->BoneSpaceTransforms;
    for (const FTransform& Transform : FirstRun)
    {
        TestFalse(TEXT("No NaN in simulated pose"), Transform.ContainsNaN());
        TestTrue(TEXT("Simulated rotations normalized"), Transform.GetRotation().IsNormalized());
    }
    const TArray<FTransform> FirstComponent = BonamikTestComponentPose(FirstRun, Mesh->RefSkeleton);
    float MaxDynamicDisplacement = 0.0f;
    float MaxDynamicRotationDegrees = 0.0f;
    int32 DynamicBoneCount = 0;
    for (const FSQEX_BonamikBodyDesc& Body : Assets[0]->mBodies)
    {
        if (Body.m_IsKinematic) continue;
        const int32 Bone = Mesh->RefSkeleton.FindBoneIndex(FName(*Body.mParentName));
        if (!TestTrue(TEXT("Genuine dynamic body resolves to an original mesh bone"), FirstComponent.IsValidIndex(Bone))) return false;
        ++DynamicBoneCount;
        MaxDynamicDisplacement = FMath::Max(MaxDynamicDisplacement,
            FVector::Dist(FirstComponent[Bone].GetTranslation(), BasePose[Bone].GetTranslation()));
        MaxDynamicRotationDegrees = FMath::Max(MaxDynamicRotationDegrees,
            FMath::RadiansToDegrees(FirstComponent[Bone].GetRotation().AngularDistance(BasePose[Bone].GetRotation())));
    }
    TestEqual(TEXT("All 220 genuine dynamic owners examined"), DynamicBoneCount, 220);
    TestTrue(TEXT("Physics produces meaningful dynamic motion, not an inert pose"),
        MaxDynamicDisplacement > 0.1f || MaxDynamicRotationDegrees > 0.1f);
    const float CharacterHeight = Mesh->GetBounds().BoxExtent.Z * 2.0f;
    TestTrue(TEXT("Dynamic displacement remains within one character height"),
        FMath::IsFinite(MaxDynamicDisplacement) && CharacterHeight > 100.0f && MaxDynamicDisplacement < CharacterHeight);
    AddInfo(FString::Printf(TEXT("BonamikNativeMotion dynamic=%d max_displacement_cm=%.6f max_rotation_deg=%.6f character_height_cm=%.6f"),
        DynamicBoneCount, MaxDynamicDisplacement, MaxDynamicRotationDegrees, CharacterHeight));
    Session.ResetSimulation();
    TestEqual(TEXT("Reset preserves genuine mesh ownership"), Target->SkeletalMesh, Mesh);
    const TArray<FTransform> ResetLocal = Target->BoneSpaceTransforms;
    const TArray<FTransform>& RefLocal = Mesh->RefSkeleton.GetRefBonePose();
    TestEqual(TEXT("Full reference bone count preserved"), ResetLocal.Num(), RefLocal.Num());
    for (int32 Index = 0; Index < RefLocal.Num(); ++Index)
        TestTrue(TEXT("Reset restores base pose"), ResetLocal[Index].Equals(RefLocal[Index], 0.001f));
    for (int32 Index = 0; Index < 120; ++Index)
        if (!Session.TickAndApply(1.0f / 60.0f, BasePose)) return false;
    for (int32 Index = 0; Index < FirstRun.Num(); ++Index)
        TestTrue(TEXT("Reset makes fixed-step replay deterministic"), FirstRun[Index].Equals(Target->BoneSpaceTransforms[Index], 0.001f));

    // A translation and yaw leave global down gravity unchanged. Local output
    // should agree despite the different world-space simulation frame.
    const FTransform MovedFrame(FRotator(0.0f, 90.0f, 0.0f), FVector(1000.0f, -300.0f, 200.0f), FVector::OneVector);
    Target->SetWorldTransform(MovedFrame);
    Session.ResetSimulation();
    for (int32 Index = 0; Index < 120; ++Index)
        if (!TestTrue(TEXT("Translated/yaw-rotated simulation remains valid"), Session.TickAndApply(1.0f / 60.0f, BasePose))) return false;
    const TArray<FTransform> MovedComponent = BonamikTestComponentPose(Target->BoneSpaceTransforms, Mesh->RefSkeleton);
    float MaxCovariantPositionError = 0.0f;
    float MaxCovariantRotationError = 0.0f;
    for (int32 Index = 0; Index < FirstComponent.Num(); ++Index)
    {
        MaxCovariantPositionError = FMath::Max(MaxCovariantPositionError,
            FVector::Dist(FirstComponent[Index].GetTranslation(), MovedComponent[Index].GetTranslation()));
        MaxCovariantRotationError = FMath::Max(MaxCovariantRotationError,
            FMath::RadiansToDegrees(FirstComponent[Index].GetRotation().AngularDistance(MovedComponent[Index].GetRotation())));
    }
    TestTrue(TEXT("Translated/yaw-rotated local pose agrees within 0.25cm"), MaxCovariantPositionError < 0.25f);
    TestTrue(TEXT("Translated/yaw-rotated local rotation agrees within 0.5degrees"), MaxCovariantRotationError < 0.5f);
    AddInfo(FString::Printf(TEXT("BonamikNativeCovariance max_position_error_cm=%.6f max_rotation_error_deg=%.6f"),
        MaxCovariantPositionError, MaxCovariantRotationError));
    Session.ResetSimulation();
    TestTrue(TEXT("Reset retains moved component frame"), Target->GetComponentTransform().Equals(MovedFrame, 0.001f));
    for (int32 Index = 0; Index < RefLocal.Num(); ++Index)
        TestTrue(TEXT("Reset in moved frame restores unsimulated local pose"), Target->BoneSpaceTransforms[Index].Equals(RefLocal[Index], 0.001f));

    const float NaN = std::numeric_limits<float>::quiet_NaN();
    for (float InvalidDelta : { -0.01f, 0.3f, NaN })
    {
        Session.TickAndApply(1.0f / 60.0f, BasePose);
        TestFalse(TEXT("Invalid direct-session delta fails closed"), Session.TickAndApply(InvalidDelta, BasePose));
        for (int32 Index = 0; Index < RefLocal.Num(); ++Index)
            TestTrue(TEXT("Invalid delta resets unsimulated pose"), Target->BoneSpaceTransforms[Index].Equals(RefLocal[Index], 0.001f));
    }
    Target->SetWorldScale3D(FVector(2.0f));
    TestFalse(TEXT("Nonunit component scale fails closed"), Session.TickAndApply(1.0f / 60.0f, BasePose));
    Target->SetWorldTransform(MovedFrame);
    const TArray<FTransform> BeforeInvalidPose = Target->BoneSpaceTransforms;
    TArray<FTransform> InvalidPose = BasePose;
    // FTransform sanitizes NaNs in diagnostic builds. A finite, non-normalized
    // quaternion exercises the pose guard without an unrelated NaN ensure.
    InvalidPose[0].SetRotation(FQuat(0.0f, 0.0f, 0.0f, 0.0f));
    TestFalse(TEXT("Non-normalized incoming animation pose fails closed"), Session.TickAndApply(1.0f / 60.0f, InvalidPose));
    for (int32 Index = 0; Index < BeforeInvalidPose.Num(); ++Index)
        TestTrue(TEXT("Rejected pose does not mutate target"), Target->BoneSpaceTransforms[Index].Equals(BeforeInvalidPose[Index], 0.001f));
    InvalidPose = BasePose;
    InvalidPose.Pop();
    TestFalse(TEXT("Incomplete animation pose fails closed"), Session.TickAndApply(1.0f / 60.0f, InvalidPose));
    Session.Clear();
    return true;
}

#endif
