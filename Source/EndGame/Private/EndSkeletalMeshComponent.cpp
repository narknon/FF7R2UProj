#include "EndSkeletalMeshComponent.h"

UEndSkeletalMeshComponent::UEndSkeletalMeshComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bUseRefPoseOnInitAnim = true;
    this->bAutoSyncAnimationOnAttach = false;
    this->bForceUpdateAnimation = false;
    this->DisableUpdateCondition = EEndAnimDisableUpdateCondition::None;
    this->bIgnoreCameraDistanceOptimization = false;
}


