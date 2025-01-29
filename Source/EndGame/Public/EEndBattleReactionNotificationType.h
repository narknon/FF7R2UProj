#pragma once
#include "CoreMinimal.h"
#include "EEndBattleReactionNotificationType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleReactionNotificationType : uint8 {
    TakeAbility,
    Animation,
    DamageSource,
    NotInvokeBPEvent = 100,
    TakeAbilityPC = NotInvokeBPEvent,
    DangerDamagePC,
};

