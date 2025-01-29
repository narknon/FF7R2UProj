#include "EndNavWorldLinkAttrIgnoreBoxComponent.h"
#include "NavAreas/NavArea_Default.h"

UEndNavWorldLinkAttrIgnoreBoxComponent::UEndNavWorldLinkAttrIgnoreBoxComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bCanEverAffectNavigation = false;
    this->AreaClass = UNavArea_Default::StaticClass();
}


