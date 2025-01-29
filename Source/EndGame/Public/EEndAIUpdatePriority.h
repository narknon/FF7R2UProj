#pragma once
#include "CoreMinimal.h"
#include "EEndAIUpdatePriority.generated.h"

UENUM(BlueprintType)
enum class EEndAIUpdatePriority : uint8 {
    VelyHigh,
    High,
    Middle,
    Low,
    Max,
};

