#pragma once
#include "CoreMinimal.h"
#include "EEndAnimationCurveType.generated.h"

UENUM(BlueprintType)
enum class EEndAnimationCurveType : uint8 {
    ZeroLoop,
    OneLoop,
    LinearZeroOneLoop,
    EaseInZeroOneLoop,
    LinearOneZero,
    EaseInOneZero,
    LinearZeroOne,
    EaseInZeroOne,
    ConstantZeroOne,
    BattleDamage00,
    BattleDamage01,
    BattleDamage02,
    BattleDamage03,
    BattleDamage04,
    BattleDamage05,
    Max,
};

