#pragma once
#include "CoreMinimal.h"
#include "EEndAnimalRunBallSelectionType.generated.h"

UENUM(BlueprintType)
enum class EEndAnimalRunBallSelectionType : uint8 {
    NearestSelf,
    NearestTarget,
    Max,
};

