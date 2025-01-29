#pragma once
#include "CoreMinimal.h"
#include "EEndIdleActionForceDeactiveType.generated.h"

UENUM(BlueprintType)
enum class EEndIdleActionForceDeactiveType : uint8 {
    Action,
    AIState,
    Interest,
    Vehicle,
    MiniGame,
    Debug,
    Max,
};

