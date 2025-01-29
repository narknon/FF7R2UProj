#include "EndVehicleRestrictedAreaSplineActor.h"
#include "EndVehicleRestrictedAreaSplineComponent.h"

AEndVehicleRestrictedAreaSplineActor::AEndVehicleRestrictedAreaSplineActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndVehicleRestrictedAreaSplineComponent>(TEXT("EndVehicleRestrictedAreaSplineComponent"));
    this->RestrictedAreaVehicleType = EEndRestrictedAreaVehicleType::Buggy;
    this->bEnableSpline = true;
    this->bEnableHeightLimit = false;
    this->HorizontalLimitDistance = -1.00f;
    this->bEnableNotify = true;
    this->SendTriggerLimitDistance = 10000.00f;
    this->SplineComponent = (UEndVehicleRestrictedAreaSplineComponent*)RootComponent;
}


