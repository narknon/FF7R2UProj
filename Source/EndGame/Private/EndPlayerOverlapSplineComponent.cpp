#include "EndPlayerOverlapSplineComponent.h"

UEndPlayerOverlapSplineComponent::UEndPlayerOverlapSplineComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->FalloffStartDistance = 200.00f;
    this->DisengageDistance = 400.00f;
    this->FalloffExtraHeight = 100.00f;
}


