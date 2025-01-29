#pragma once
#include "CoreMinimal.h"
#include "EEndAIFollowPosition.generated.h"

UENUM(BlueprintType)
enum class EEndAIFollowPosition : uint8 {
    NONE,
    FORWARD,
    BACKWARD,
    BACKWARD_SUB,
    MAX,
};

