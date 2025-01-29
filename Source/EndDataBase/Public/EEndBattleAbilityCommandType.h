#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAbilityCommandType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleAbilityCommandType : uint8 {
    None,
    Ability,
    Magic,
    Limit,
    Item,
    CombinationAbility,
    Max,
};

