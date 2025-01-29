#include "EndFeelerAttendantActor.h"

AEndFeelerAttendantActor::AEndFeelerAttendantActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->InstanceCount = 9;
    this->RandomSeed = 0;
    this->FollowSocketName = TEXT("C_Head_a");
    this->FollowPositionInterpRate = 1.00f;
    this->SkeletalMesh = NULL;
    this->AnimationBlueprint = NULL;
    this->WalkTransitionDeltaSizeThreshold = 300.00f;
    this->WalkTransitionVelocityThreshold = 1.00f;
    this->RotationInterpSpeed = 5.00f;
    this->bAlwaysWalking = false;
    this->AttachDelayTime = 0.00f;
    this->PerformanceModeReductionRate = 0.60f;
    this->EmissiveColorSettings = NULL;
}


