#include "EndVehicleSpeedLimitVolume.h"

AEndVehicleSpeedLimitVolume::AEndVehicleSpeedLimitVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->TargetVehicleType = EEndRestrictedAreaVehicleType::Buggy;
    this->TargetSpeed = 100.00f;
    this->Priority = 0;
}


