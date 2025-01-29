#pragma once
#include "CoreMinimal.h"
#include "EEndAnimNotifyBattleUniqueAbilityGraniteJailActionType.generated.h"

UENUM(BlueprintType)
enum class EEndAnimNotifyBattleUniqueAbilityGraniteJailActionType : uint8 {
    None,
    Start,
    Finish,
    NotifyParents,
};

