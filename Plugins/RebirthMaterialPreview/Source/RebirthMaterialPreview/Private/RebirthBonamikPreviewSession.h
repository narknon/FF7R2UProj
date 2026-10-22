#pragma once

#include "CoreMinimal.h"
#include "RebirthBonamikPreviewSolver.h"

class UPoseableMeshComponent;
class USkeletalMesh;
class USQEX_BonamikAsset;

// Private, non-reflected editor helper. Own one session per preview viewport.
// Reuses the previous Tres custom solver; it does not run the retail solver.
class FRebirthBonamikPreviewSession
{
public:
    static void FindLoadedAssets(USkeletalMesh* Mesh, TArray<USQEX_BonamikAsset*>& OutAssets);
    // Runtime preview: binds the solver to a transient poseable component that TickAndApply writes.
    bool Initialize(UPoseableMeshComponent* InTarget, USQEX_BonamikAsset* Source, FString& OutStatus);
    // Component-independent: builds the solver for Mesh's reference skeleton (Source must be attached to Mesh).
    bool InitializeForMesh(USkeletalMesh* InMesh, USQEX_BonamikAsset* Source, FString& OutStatus);
    void ResetSimulation();
    void Clear();
    // One solver step from an animated component-space pose to a simulated component-space pose (all bones).
    // Writes nothing but OutComponentPose; returns false (pose untouched) when the input cannot be simulated.
    bool Simulate(float DeltaSeconds, const FTransform& ComponentToWorld,
        const TArray<FTransform>& AnimatedComponentPose, TArray<FTransform>& OutComponentPose);
    bool TickAndApply(float DeltaSeconds, const TArray<FTransform>& AnimatedComponentPose);
    USkeletalMesh* GetMesh() const { return Mesh.Get(); }
    int32 GetBoneCount() const { return Parents.Num(); }
    const TArray<FTransform>& GetReferenceComponentPose() const { return ReferenceComponentPose; }
    const FString& GetStatus() const { return Status; }
    bool IsReady() const { return Solver.IsReady(); }
    int32 GetBodyCount() const { return Solver.GetParticleCount(); }
    int32 GetAttachmentCount() const { return Solver.GetAttachmentCount(); }
    int32 GetAuthoredShapeCount() const { return Solver.GetAuthoredShapeCount(); }
    int32 GetAuthoredCollisionPairCount() const { return Solver.GetAuthoredCollisionPairCount(); }

private:
    TWeakObjectPtr<UPoseableMeshComponent> Target;
    TWeakObjectPtr<USkeletalMesh> Mesh;
    TArray<int32> Parents;
    TArray<FTransform> ReferenceComponentPose;
    TArray<FTransform> LastAnimatedComponentPose;
    FRebirthBonamikPreviewSolver Solver;
    FRebirthBonamikPreviewSettings Settings;
    FString Status;
};
