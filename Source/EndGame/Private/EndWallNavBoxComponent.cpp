#include "EndWallNavBoxComponent.h"
#include "NavAreas/NavArea_Obstacle.h"

UEndWallNavBoxComponent::UEndWallNavBoxComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AreaClass = UNavArea_Obstacle::StaticClass();
    this->BoxID = 0;
}


