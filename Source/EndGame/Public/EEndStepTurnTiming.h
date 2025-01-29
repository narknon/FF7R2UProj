#pragma once
#include "CoreMinimal.h"
#include "EEndStepTurnTiming.generated.h"

UENUM(BlueprintType)
enum class EEndStepTurnTiming : uint8 {
    None,
    MoveStart,
    MoveEnd,
    TurnStart,
    TurnEnd,
};

