#include "EndCinemaMaterialAnimateTimeComponent.h"

UEndCinemaMaterialAnimateTimeComponent::UEndCinemaMaterialAnimateTimeComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bNormalized = false;
    this->AnimateTime = 0.00f;
}


