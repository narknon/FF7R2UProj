#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAbilityTeleportType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleAbilityTeleportType : uint8 {
    None,
    CombinationTarget,
    ToCombinationExecutor,
    NearCombinationExecutor,
    SideCombinationExecutor,
    FBCombinationExecutor,
    ToCombinationExecutorSocket,
    ToAbilityApproachPoint,
};

