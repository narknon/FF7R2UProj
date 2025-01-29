#pragma once
#include "CoreMinimal.h"
#include "EEndSpecificMoveType.generated.h"

UENUM(BlueprintType)
enum class EEndSpecificMoveType : uint8 {
    Walk,
    HighWalk,
    Jog,
    Run,
    None,
    Max,
    Empty,
};

