#include "EndVehicleSpeedLimitVolumeSplineActor.h"

AEndVehicleSpeedLimitVolumeSplineActor::AEndVehicleSpeedLimitVolumeSplineActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->TargetSpeed = 100.00f;
    this->TargetSpeedTowardSplineNormal = 200.00f;
    this->Priority = 0;
}


