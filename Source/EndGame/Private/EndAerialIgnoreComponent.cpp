#include "EndAerialIgnoreComponent.h"

UEndAerialIgnoreComponent::UEndAerialIgnoreComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bHiddenInGame = true;
    this->MeshShapeType = EAerialIgnoreShapeType::Box;
    this->SphereRadius = 50.00f;
}


