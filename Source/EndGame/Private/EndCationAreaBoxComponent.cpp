#include "EndCationAreaBoxComponent.h"
#include "EndNavAreaCation.h"

UEndCationAreaBoxComponent::UEndCationAreaBoxComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AreaClass = UEndNavAreaCation::StaticClass();
}


