#pragma once
#include "CoreMinimal.h"
#include "EPartyVehicleRideStatus.generated.h"

UENUM(BlueprintType)
enum class EPartyVehicleRideStatus : uint8 {
    GetOffStable,
    RideOnRunning,
    RideOnStable,
    GetOffRunning,
};

