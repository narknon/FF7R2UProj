#pragma once
#include "CoreMinimal.h"
#include "EAutoMagicSelectRuleType.generated.h"

UENUM(BlueprintType)
enum class EAutoMagicSelectRuleType : uint8 {
    None,
    LowHpRate,
    LowHpRateAndMaxHp,
    HighMaxHp,
    LowDefence,
    LowStatusResist,
    HighPopulation,
    StatusChange,
};

