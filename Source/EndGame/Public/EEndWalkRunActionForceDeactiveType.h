#pragma once
#include "CoreMinimal.h"
#include "EEndWalkRunActionForceDeactiveType.generated.h"

UENUM(BlueprintType)
enum class EEndWalkRunActionForceDeactiveType : uint8 {
    AIState,
    AIMove,
    Debug,
    Max,
};

