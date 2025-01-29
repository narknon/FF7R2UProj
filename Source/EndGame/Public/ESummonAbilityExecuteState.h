#pragma once
#include "CoreMinimal.h"
#include "ESummonAbilityExecuteState.generated.h"

UENUM(BlueprintType)
enum class ESummonAbilityExecuteState : uint8 {
    eNone,
    eRequesting,
    eInAction,
    eCompleted,
};

