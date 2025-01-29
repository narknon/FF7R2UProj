#include "EndSwitchAreaBoxComponent.h"
#include "EndNavAreaVersatile.h"

UEndSwitchAreaBoxComponent::UEndSwitchAreaBoxComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bCanEverAffectNavigation = false;
    this->AreaClass = UEndNavAreaVersatile::StaticClass();
}


