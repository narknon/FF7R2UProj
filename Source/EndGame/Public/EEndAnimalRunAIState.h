#pragma once
#include "CoreMinimal.h"
#include "EEndAnimalRunAIState.generated.h"

UENUM(BlueprintType)
enum class EEndAnimalRunAIState : uint8 {
    Wandering,
    Attacker,
    GoalKeeper,
};

