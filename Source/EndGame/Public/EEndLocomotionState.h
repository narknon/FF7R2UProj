#pragma once
#include "CoreMinimal.h"
#include "EEndLocomotionState.generated.h"

UENUM(BlueprintType)
enum class EEndLocomotionState : uint8 {
    Idle,
    Turn,
    WalkStart,
    WalkLoop,
    WalkEnd,
    WalkTurn,
    RunStart,
    RunLoop,
    RunEnd,
    RunTurn,
    DashStart,
    DashLoop,
    DashEnd,
    StrafingWalkStart,
    StrafingWalkLoop,
    StrafingWalkEnd,
    AccelLoop,
    SwitchBehavior,
    FallLoop,
    FallEnd,
    Max,
};

