#pragma once
#include "CoreMinimal.h"
#include "EClimbingJumpPointType.generated.h"

UENUM(BlueprintType)
enum class EClimbingJumpPointType : uint8 {
    ToClimbing,
    ToHookRope,
    MAX,
};

