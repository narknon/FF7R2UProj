#pragma once
#include "CoreMinimal.h"
#include "EHookRopeJumpPointType.generated.h"

UENUM(BlueprintType)
enum class EHookRopeJumpPointType : uint8 {
    ToGround,
    ToClimbing,
    ToHookRope,
    ToFall,
    MAX,
};

