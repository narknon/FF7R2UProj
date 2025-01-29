#pragma once
#include "CoreMinimal.h"
#include "EEndFieldMoveType.generated.h"

UENUM(BlueprintType)
enum class EEndFieldMoveType : uint8 {
    None,
    Idle,
    Walk,
    HighWalk,
    Jog,
    Run,
    Dash,
};

