#pragma once
#include "CoreMinimal.h"
#include "EEndClimbingPointType.generated.h"

UENUM(BlueprintType)
enum class EEndClimbingPointType : uint8 {
    HookRope,
    Climbing,
    ClimbingStartEnd,
    HookRopeStart,
    HookRopeLand,
    MAX,
};

