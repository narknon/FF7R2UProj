#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAbilityAfterTeleportRotationType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleAbilityAfterTeleportRotationType : uint8 {
    ToTarget,
    SameCombinationExecutor,
    SameCombinationExecutorPriorityTarget,
    InverseCombinationExecutor,
    ToCombinationExecutor,
};

