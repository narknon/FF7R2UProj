#include "EndSpiderWallEntryAreaBoxComponent.h"
#include "NavAreas/NavArea_Default.h"

UEndSpiderWallEntryAreaBoxComponent::UEndSpiderWallEntryAreaBoxComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bCanEverAffectNavigation = false;
    this->AreaClass = UNavArea_Default::StaticClass();
    this->bDisableEntry = false;
    this->bHideEntryEffect = false;
    this->bCachedAroundFixCatchTrans = false;
    this->bCachedEdgeTrans = false;
}


