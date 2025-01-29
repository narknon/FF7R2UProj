#pragma once
#include "CoreMinimal.h"
#include "EEndBattleStatusChangeTimeType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleStatusChangeTimeType : uint8 {
    Short,
    Middle,
    Long,
    Infinity = 64,
};

