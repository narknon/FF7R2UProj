#pragma once
#include "CoreMinimal.h"
#include "EEndAnimalRunAIPhase.generated.h"

UENUM(BlueprintType)
enum class EEndAnimalRunAIPhase : uint8 {
    None,
    Prepare,
    Shoot,
    Chase,
    Dribble,
    WaitAirBall,
    Rest,
    StandBy,
    Defence,
    Wandering,
};

