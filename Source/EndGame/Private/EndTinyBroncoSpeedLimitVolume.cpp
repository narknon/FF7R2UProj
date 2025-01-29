#include "EndTinyBroncoSpeedLimitVolume.h"
#include "EEndRestrictedAreaVehicleType.h"

AEndTinyBroncoSpeedLimitVolume::AEndTinyBroncoSpeedLimitVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->TargetVehicleType = EEndRestrictedAreaVehicleType::TinyBronco;
}


