#include "EndBonamikCapsuleWorldWindModifyComponent.h"

UEndBonamikCapsuleWorldWindModifyComponent::UEndBonamikCapsuleWorldWindModifyComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->WindAsset = NULL;
    this->Scale = 1.00f;
    this->bDisableWorldWind = false;
    this->bEnabled = true;
    this->bDebugDraw = false;
}


