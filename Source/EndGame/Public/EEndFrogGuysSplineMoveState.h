#pragma once
#include "CoreMinimal.h"
#include "EEndFrogGuysSplineMoveState.generated.h"

UENUM(BlueprintType)
enum class EEndFrogGuysSplineMoveState : uint8 {
    StartStop,
    MoveForward,
    EndStop,
    MoveBack,
    Loop,
};

