#pragma once
#include "CoreMinimal.h"
#include "EEndChocoboPlayerMoveState.generated.h"

UENUM(BlueprintType)
enum class EEndChocoboPlayerMoveState : uint8 {
    Idle,
    Walk,
    Run,
    Dash,
    Max,
};

