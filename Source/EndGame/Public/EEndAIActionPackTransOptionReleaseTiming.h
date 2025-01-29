#pragma once
#include "CoreMinimal.h"
#include "EEndAIActionPackTransOptionReleaseTiming.generated.h"

UENUM(BlueprintType)
enum class EEndAIActionPackTransOptionReleaseTiming : uint8 {
    ActionAfter,
    Keep,
    ForceRelease,
};

