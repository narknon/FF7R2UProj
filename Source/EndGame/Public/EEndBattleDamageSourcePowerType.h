#pragma once
#include "CoreMinimal.h"
#include "EEndBattleDamageSourcePowerType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleDamageSourcePowerType : uint8 {
    Normal,
    Constant,
    Attack,
    MaxHPPercentTarget,
    MaxHPPercentOwner,
    HPPercentTarget,
    HPPercentOwner,
    DecreaseHPPercentTarget,
    DecreaseHPPercentOwner,
    MaxMPPercentTarget,
    ATBPercent,
    HPOneSingleDigit,
    ParentDamageValue,
    MulDecreaseHPRateOwner,
    TypeMaxPercentRevengeGaugeRateOwner,
    Zeninage,
    AbilityHPDamageHitCount,
    ConstantIgnoreResist_BurstFont,
};

