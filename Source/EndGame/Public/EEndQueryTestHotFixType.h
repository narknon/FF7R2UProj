#pragma once
#include "CoreMinimal.h"
#include "EEndQueryTestHotFixType.generated.h"

UENUM(BlueprintType)
enum class EEndQueryTestHotFixType : uint8 {
    None,
    BattleIn,
    BattleOut,
    AbilityJump,
    Combination,
};

