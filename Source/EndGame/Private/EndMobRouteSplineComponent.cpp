#include "EndMobRouteSplineComponent.h"
#include "EndMobRouteSplineMetadata.h"

UEndMobRouteSplineComponent::UEndMobRouteSplineComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->MobRouteSplineMetadata = CreateDefaultSubobject<UEndMobRouteSplineMetadata>(TEXT("MobRouteSplineMetadata"));
}


