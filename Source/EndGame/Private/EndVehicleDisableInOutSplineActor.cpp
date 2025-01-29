#include "EndVehicleDisableInOutSplineActor.h"
#include "EndVehicleDisableInOutSplineComponent.h"

AEndVehicleDisableInOutSplineActor::AEndVehicleDisableInOutSplineActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UEndVehicleDisableInOutSplineComponent>(TEXT("EndVehicleDisableInOutSplineComponent"));
    this->TatgetVehicleType = EEndPlayerVehicleType::None;
    this->SplineComponent = (UEndVehicleDisableInOutSplineComponent*)RootComponent;
}


