#include "EndPBDIgnoreCollisionEdgeComponent.h"
#include "NavAreas/NavArea_Obstacle.h"

UEndPBDIgnoreCollisionEdgeComponent::UEndPBDIgnoreCollisionEdgeComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AreaClass = UNavArea_Obstacle::StaticClass();
}


