#pragma once
#include "CoreMinimal.h"
#include "EEndAnimalRunTargetCorrectionType.generated.h"

UENUM(BlueprintType)
enum class EEndAnimalRunTargetCorrectionType : uint8 {
    TargetGoal,
    TargetBall,
    Shoot,
};

