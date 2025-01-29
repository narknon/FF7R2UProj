#pragma once
#include "CoreMinimal.h"
#include "EEndAIActionMoveTimeOut.generated.h"

UENUM(BlueprintType)
enum class EEndAIActionMoveTimeOut : uint8 {
    StandardMove,
    ActionMove,
    Max,
    None,
};

