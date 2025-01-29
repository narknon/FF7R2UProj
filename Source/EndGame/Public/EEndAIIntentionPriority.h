#pragma once
#include "CoreMinimal.h"
#include "EEndAIIntentionPriority.generated.h"

UENUM(BlueprintType)
enum class EEndAIIntentionPriority : uint8 {
    RuleBased,
    High,
    Middle,
    Low,
    Max,
};

