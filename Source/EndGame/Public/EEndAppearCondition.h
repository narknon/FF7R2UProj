#pragma once
#include "CoreMinimal.h"
#include "EEndAppearCondition.generated.h"

UENUM(BlueprintType)
enum class EEndAppearCondition : uint8 {
    None,
    Time,
    LeftTime,
    EnemyLeft,
    DefeatEnemyCount,
};

