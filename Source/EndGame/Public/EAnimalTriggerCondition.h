#pragma once
#include "CoreMinimal.h"
#include "EAnimalTriggerCondition.generated.h"

UENUM(BlueprintType)
enum class EAnimalTriggerCondition : uint8 {
    GameStart,
    GameEnd,
    SameGoalBall,
    GoalA,
    GoalB,
    GoalC,
    GoalD,
    Max,
};

