#pragma once
#include "CoreMinimal.h"
#include "EEndVehicleZeroOneValueSourceTypes.generated.h"

UENUM(BlueprintType)
namespace EEndVehicleZeroOneValueSourceTypes {
    enum Type {
        ScaledVelocity,
        ScaledRollAngle,
        ScaledRotationalVelocity,
        ScaledWheelVelocity,
        MAX,
    };
}

