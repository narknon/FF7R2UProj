#include "EndBonamikBoxWindComponent.h"

UEndBonamikBoxWindComponent::UEndBonamikBoxWindComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->WindAsset = NULL;
    this->Scale = 1.00f;
    this->bDisableWorldWind = true;
    this->bEnabled = true;
    this->bDebugDraw = false;
}


