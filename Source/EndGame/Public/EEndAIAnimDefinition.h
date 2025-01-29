#pragma once
#include "CoreMinimal.h"
#include "EEndAIAnimDefinition.generated.h"

UENUM(BlueprintType)
enum class EEndAIAnimDefinition : uint8 {
    Normal,
    Avoid,
    Max,
};

