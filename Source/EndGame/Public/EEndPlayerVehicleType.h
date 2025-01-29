#pragma once
#include "CoreMinimal.h"
#include "EEndPlayerVehicleType.generated.h"

UENUM(BlueprintType)
enum class EEndPlayerVehicleType : uint8 {
    None,
    Chocobo,
    Buggy,
    TinyBronco,
    SelfBalancingScooter,
    CaitSithFatMoogle,
    Max,
};

