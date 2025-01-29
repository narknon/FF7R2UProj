#pragma once
#include "CoreMinimal.h"
#include "EEndAnimNotifyBattleDamageCondition.generated.h"

UENUM(BlueprintType)
enum class EEndAnimNotifyBattleDamageCondition : uint8 {
    None,
    CombinationTriggerDamageHit,
    UseCombinationAbilityWithCombinationPartner,
};

