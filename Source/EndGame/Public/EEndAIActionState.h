#pragma once
#include "CoreMinimal.h"
#include "EEndAIActionState.generated.h"

UENUM(BlueprintType)
enum class EEndAIActionState : uint8 {
    Standby,
    Move,
    Step00,
    Step01,
    Action,
};

