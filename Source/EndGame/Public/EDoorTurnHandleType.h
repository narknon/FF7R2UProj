#pragma once
#include "CoreMinimal.h"
#include "EDoorTurnHandleType.generated.h"

UENUM(BlueprintType)
enum class EDoorTurnHandleType : uint8 {
    None,
    TurnHandleRight,
    TurnHandleLeft,
    Invalid,
};

