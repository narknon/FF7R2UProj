#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAttributeResistType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleAttributeResistType : uint8 {
    None,
    Weak,
    HalfDecrease,
    LargeDecrease,
    Resist,
    Absorb,
};

