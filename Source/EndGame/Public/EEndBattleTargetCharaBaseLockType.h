#pragma once
#include "CoreMinimal.h"
#include "EEndBattleTargetCharaBaseLockType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleTargetCharaBaseLockType : uint8 {
    Ability,
    Combo,
    AI,
    MAX,
};

