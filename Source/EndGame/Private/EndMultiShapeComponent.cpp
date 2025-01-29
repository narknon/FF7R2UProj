#include "EndMultiShapeComponent.h"

UEndMultiShapeComponent::UEndMultiShapeComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bHiddenInGame = true;
    this->bCastDynamicShadow = false;
    this->ShapeBodySetup = NULL;
}


