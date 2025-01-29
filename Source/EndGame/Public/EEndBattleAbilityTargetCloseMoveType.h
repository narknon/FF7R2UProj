#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAbilityTargetCloseMoveType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleAbilityTargetCloseMoveType : uint8 {
    Stop,
    None,
    Push,
};

