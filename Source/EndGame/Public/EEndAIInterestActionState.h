#pragma once
#include "CoreMinimal.h"
#include "EEndAIInterestActionState.generated.h"

UENUM(BlueprintType)
enum class EEndAIInterestActionState : uint8 {
    Pending,
    Playing,
    Suspended,
    Completed,
    Max,
};

