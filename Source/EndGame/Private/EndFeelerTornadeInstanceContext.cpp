#include "EndFeelerTornadeInstanceContext.h"

FEndFeelerTornadeInstanceContext::FEndFeelerTornadeInstanceContext() {
    this->InstanceIndex = 0;
    this->VerticalHeightOffset = 0.00f;
    this->TargetExtrusionDistance = 0.00f;
    this->CurrentExtrusionDistance = 0.00f;
    this->ExtrusionWaitTimer = 0.00f;
    this->SkeletalMeshComponent = NULL;
    this->InstancedStaticMeshComponentIndex = 0;
    this->InstancedStaticMeshInstanceIndex = 0;
    this->bVisibility = false;
}

