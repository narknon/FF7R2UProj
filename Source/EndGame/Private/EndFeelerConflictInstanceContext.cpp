#include "EndFeelerConflictInstanceContext.h"

FEndFeelerConflictInstanceContext::FEndFeelerConflictInstanceContext() {
    this->InstanceIndex = 0;
    this->bIsSideB = false;
    this->bLose = false;
    this->bLastLose = false;
    this->LoseFadeWaitTime = 0.00f;
    this->LoseFadeAlpha = 0.00f;
    this->LoseVelocityAlpha = 0.00f;
    this->WinRate = 0.00f;
    this->LastHorizontalTimeRate = 0.00f;
    this->SkeletalMeshComponent = NULL;
    this->bVisibility = false;
}

