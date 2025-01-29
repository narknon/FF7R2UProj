#include "EndOverlapCapsuleComponent.h"
#include "NavAreas/NavArea_Obstacle.h"

UEndOverlapCapsuleComponent::UEndOverlapCapsuleComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AreaClass = UNavArea_Obstacle::StaticClass();
}


