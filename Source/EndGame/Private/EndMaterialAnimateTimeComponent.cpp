#include "EndMaterialAnimateTimeComponent.h"

UEndMaterialAnimateTimeComponent::UEndMaterialAnimateTimeComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->Duration = 1.00f;
    this->AnimateTime = 0.00f;
}


