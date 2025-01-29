#pragma once
#include "CoreMinimal.h"
#include "EAutoMagicEssentialConditionType.generated.h"

UENUM(BlueprintType)
enum class EAutoMagicEssentialConditionType : uint8 {
    MpRateForHighestRank,
    PlayerOperateTime,
    ExistsResistableStatusChange,
};

