#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAISelectTargetType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleAISelectTargetType : uint8 {
    None,
    Hate,
    Condition,
    Max,
};

