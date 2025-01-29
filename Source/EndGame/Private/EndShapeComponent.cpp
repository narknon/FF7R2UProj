#include "EndShapeComponent.h"

UEndShapeComponent::UEndShapeComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bHiddenInGame = true;
    this->bCastDynamicShadow = false;
    this->ShapeType = EEndCollision::SPHERE;
    this->ShapeMesh = NULL;
    this->ShapeBodySetup = NULL;
}


