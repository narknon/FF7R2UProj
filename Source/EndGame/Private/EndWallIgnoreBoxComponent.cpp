#include "EndWallIgnoreBoxComponent.h"
#include "NavAreas/NavArea_Obstacle.h"

UEndWallIgnoreBoxComponent::UEndWallIgnoreBoxComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AreaClass = UNavArea_Obstacle::StaticClass();
}


