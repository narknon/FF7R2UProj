#pragma once
#include "CoreMinimal.h"
#include "EEndAIGuardDefinition.generated.h"

UENUM(BlueprintType)
enum class EEndAIGuardDefinition : uint8 {
    Normal,
    ParallelMove,
    Reaction,
    Max,
};

