#pragma once
#include "CoreMinimal.h"
#include "EBattleInputAttackType.generated.h"

UENUM(BlueprintType)
enum class EBattleInputAttackType : uint8 {
    None = 255,
    Normal = 0,
    Unique,
};

