#include "EndOceanDisplacementComponent.h"

UEndOceanDisplacementComponent::UEndOceanDisplacementComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->OceanDisplacementDataAsset = NULL;
    this->OceanMaterialAnimateTimeComponent = NULL;
}


