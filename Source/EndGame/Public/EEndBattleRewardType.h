#pragma once
#include "CoreMinimal.h"
#include "EEndBattleRewardType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleRewardType : uint8 {
    Exp,
    Ap,
    Gil,
    Drop,
    Steal,
};

