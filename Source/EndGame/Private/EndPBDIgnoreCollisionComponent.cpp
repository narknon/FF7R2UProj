#include "EndPBDIgnoreCollisionComponent.h"
#include "NavAreas/NavArea_Obstacle.h"

UEndPBDIgnoreCollisionComponent::UEndPBDIgnoreCollisionComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bCanEverAffectNavigation = false;
    this->AreaClass = UNavArea_Obstacle::StaticClass();
    this->bIgnoreEdge = false;
    this->CollisionGroup = 0;
}


