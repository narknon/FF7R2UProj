#include "EndFieldMovementControlSplineComponent.h"

UEndFieldMovementControlSplineComponent::UEndFieldMovementControlSplineComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bSnapPosition = true;
    this->bSnapRotation = true;
}


