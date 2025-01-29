#include "EndBonamikBoxWorldWindModifyComponent.h"

UEndBonamikBoxWorldWindModifyComponent::UEndBonamikBoxWorldWindModifyComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->WindAsset = NULL;
    this->Scale = 1.00f;
    this->bEnabled = true;
    this->bDebugDraw = false;
}


