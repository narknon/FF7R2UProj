#include "EndFieldMineCartTargetComponent.h"

UEndFieldMineCartTargetComponent::UEndFieldMineCartTargetComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->MineCartActor = NULL;
    this->DisablePushFromFront = false;
    this->DisablePushFromBack = false;
}


