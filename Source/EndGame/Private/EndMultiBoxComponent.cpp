#include "EndMultiBoxComponent.h"
#include "EndNavAreaVersatile.h"

UEndMultiBoxComponent::UEndMultiBoxComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bCanEverAffectNavigation = false;
    this->AreaClass = UEndNavAreaVersatile::StaticClass();
}


