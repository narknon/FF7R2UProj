#pragma once
#include "CoreMinimal.h"
#include "EEndAnimalRunAngleType.generated.h"

UENUM(BlueprintType)
enum class EEndAnimalRunAngleType : uint8 {
    OwnerForward,
    BallMoveDirection,
    TargetGoalForward,
    SelfGoalForward,
    BallToTargetGoal,
    OwnerToBall,
    OwnerToTargetGoal,
};

