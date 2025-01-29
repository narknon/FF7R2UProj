#include "EndStaticMeshPhysicsPartsComponent.h"

UEndStaticMeshPhysicsPartsComponent::UEndStaticMeshPhysicsPartsComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bCanEverAffectNavigation = false;
}


