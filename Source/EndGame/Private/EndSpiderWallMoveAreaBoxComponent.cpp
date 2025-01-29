#include "EndSpiderWallMoveAreaBoxComponent.h"
#include "NavAreas/NavArea_Default.h"

UEndSpiderWallMoveAreaBoxComponent::UEndSpiderWallMoveAreaBoxComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bCanEverAffectNavigation = false;
    this->AreaClass = UNavArea_Default::StaticClass();
}


