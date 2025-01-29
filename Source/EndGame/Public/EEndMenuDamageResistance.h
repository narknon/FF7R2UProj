#pragma once
#include "CoreMinimal.h"
#include "EEndMenuDamageResistance.generated.h"

UENUM(BlueprintType)
enum class EEndMenuDamageResistance : uint8 {
    None,
    Weakness,
    Reduced,
};

