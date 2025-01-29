#pragma once
#include "CoreMinimal.h"
#include "EEndWalkRestriction.generated.h"

UENUM(BlueprintType)
enum class EEndWalkRestriction : uint8 {
    None,
    LimitedDash,
    LimitedRunning,
    LimitedWalking,
};

