#pragma once
#include "CoreMinimal.h"
#include "EEndChocoboRaceAbility.generated.h"

UENUM(BlueprintType)
enum class EEndChocoboRaceAbility : uint8 {
    Boost,
    SuperArmor,
    Shot,
    Jump,
    Hover,
    Homing,
    FullPower,
    Max,
};

