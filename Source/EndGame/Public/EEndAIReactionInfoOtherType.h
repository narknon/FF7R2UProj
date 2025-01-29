#pragma once
#include "CoreMinimal.h"
#include "EEndAIReactionInfoOtherType.generated.h"

UENUM(BlueprintType)
enum class EEndAIReactionInfoOtherType : uint8 {
    UniqueAbility,
    CombinationAbility_NoUseATB,
    Max,
};

