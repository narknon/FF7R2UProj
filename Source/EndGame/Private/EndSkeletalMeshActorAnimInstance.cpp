#include "EndSkeletalMeshActorAnimInstance.h"

UEndSkeletalMeshActorAnimInstance::UEndSkeletalMeshActorAnimInstance() {
    this->PlayRate = 1.00f;
    this->bPlayingCutScene = false;
    this->bPlayingDialogue = false;
    this->bRequestedPoseTransition = false;
    this->RequestedPoseTransitionBlendTime = -1.00f;
}


