#include "EndFeelerFollowingActor.h"

AEndFeelerFollowingActor::AEndFeelerFollowingActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->InstanceCount = 9;
    this->RandomSeed = 0;
    this->ActorFollowInterpSpeed = 20.00f;
    this->RadiusInterpSpeed = 0.80f;
    this->HeightInterpSpeed = 15.00f;
    this->RotationInterpSpeed = 20.00f;
    this->MoveInTime = 3.00f;
    this->MoveOutTime = 3.00f;
    this->MoveInVelocityBias = 1.00f;
    this->MoveOutVelocityBias = 1.00f;
    this->FadeInTime = 1.00f;
    this->FadeOutTime = 1.00f;
    this->SkeletalMeshA = NULL;
    this->SkeletalMeshB = NULL;
    this->AnimClass = NULL;
    this->MeshRate = 0.00f;
    this->PerformanceModeReductionRate = 0.60f;
    this->EmissiveColorSettingsA = NULL;
    this->EmissiveColorSettingsB = NULL;
}


