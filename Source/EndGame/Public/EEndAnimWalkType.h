#pragma once
#include "CoreMinimal.h"
#include "EEndAnimWalkType.generated.h"

UENUM(BlueprintType)
enum class EEndAnimWalkType : uint8 {
    Idle,
    Walk,
    HighWalk,
    Jog,
    Run,
    Dash,
    Max,
};

