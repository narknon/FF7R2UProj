#include "EndUniqueSimpleCollisionComponent.h"

UEndUniqueSimpleCollisionComponent::UEndUniqueSimpleCollisionComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bHiddenInGame = true;
    this->bCastDynamicShadow = false;
    this->BodySetup = NULL;
}


