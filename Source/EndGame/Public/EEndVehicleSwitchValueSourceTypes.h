#pragma once
#include "CoreMinimal.h"
#include "EEndVehicleSwitchValueSourceTypes.generated.h"

UENUM(BlueprintType)
namespace EEndVehicleSwitchValueSourceTypes {
    enum Type {
        None,
        ScaledVelocity,
        ScaledRollAngle,
        ScaledWheelVelocity,
        EngineZeroOneSlot0,
        EngineZeroOneSlot1,
        TravelingZeroOneSlot0,
        TravelingZeroOneSlot1,
        WindNoiseZeroOneSlot0,
        WindNoiseZeroOneSlot1,
        MAX,
    };
}

