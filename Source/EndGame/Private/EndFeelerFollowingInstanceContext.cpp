#include "EndFeelerFollowingInstanceContext.h"

FEndFeelerFollowingInstanceContext::FEndFeelerFollowingInstanceContext() {
    this->InstanceIndex = 0;
    this->CurrentVelocityBias = 0.00f;
    this->SkeletalMeshComponent = NULL;
    this->bSideA = false;
}

