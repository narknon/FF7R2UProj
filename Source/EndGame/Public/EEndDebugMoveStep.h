#pragma once
#include "CoreMinimal.h"
#include "EEndDebugMoveStep.generated.h"

UENUM(BlueprintType)
enum class EEndDebugMoveStep : uint8 {
    None,
    DebugMoveStart,
    DebugMoving,
    DebugMoveEnd,
};

