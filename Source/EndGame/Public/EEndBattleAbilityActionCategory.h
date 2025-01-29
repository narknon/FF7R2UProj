#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAbilityActionCategory.generated.h"

UENUM(BlueprintType)
enum class EEndBattleAbilityActionCategory : uint8 {
    None,
    DamageToOpponent,
    DebuffToOpponent,
    BuffToAlly,
    RecoverToAlly,
};

