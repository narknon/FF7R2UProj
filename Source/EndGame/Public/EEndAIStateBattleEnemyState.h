#pragma once
#include "CoreMinimal.h"
#include "EEndAIStateBattleEnemyState.generated.h"

UENUM(BlueprintType)
enum class EEndAIStateBattleEnemyState : uint8 {
    STATE_STANDBY,
    STATE_ATTACK,
    STATE_WAIT,
    STATE_PROWL,
    STATE_REACTION,
    STATE_FORCE_ACTION,
    STATE_COMBINATION,
    STATE_RETURN_TO_BATTLE_AREA,
};

