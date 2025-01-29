#include "EndBonamikRaycastWindComponent.h"

UEndBonamikRaycastWindComponent::UEndBonamikRaycastWindComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->WindAsset = NULL;
    this->RaycastLength = 500.00f;
    this->WindScale = 1.00f;
    this->bDisableWorldWind = true;
    this->bEnabled = true;
    this->bDebugDraw = true;
}


