#include "EndMaterialAnimateTimeUnnormalizedComponent.h"

UEndMaterialAnimateTimeUnnormalizedComponent::UEndMaterialAnimateTimeUnnormalizedComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PlayRate = 1.00f;
    this->bSetToNormalized = false;
    this->AnimateTime = 0.00f;
}


