#pragma once
#include "CoreMinimal.h"
#include "EEndCactusMissionMiniGameEnemyType.generated.h"

UENUM(BlueprintType)
enum class EEndCactusMissionMiniGameEnemyType : uint8 {
    NORMAL,
    NORMAL_L,
    SHOOTER,
    CORTENDER,
    TIME_PLUS,
    MAX,
};

