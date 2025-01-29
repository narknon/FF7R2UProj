#include "SQEXSEADLayoutComponent.h"

USQEXSEADLayoutComponent::USQEXSEADLayoutComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->Sound = NULL;
    this->bIgnoreObstruction = false;
    this->bOverrideInteriorFactor = false;
    this->InteriorFactor = 0.00f;
    this->VolumeMultiplier = 0.00f;
    this->PitchMultiplier = 0.00f;
}


