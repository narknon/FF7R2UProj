#pragma once
#include "CoreMinimal.h"
#include "EEndClimbingContinueFromType.generated.h"

UENUM(BlueprintType)
enum class EEndClimbingContinueFromType : uint8 {
    Ground,
    Climbing,
    Tarzan,
    ClimbingRope,
    MAX,
};

