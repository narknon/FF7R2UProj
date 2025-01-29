#pragma once
#include "CoreMinimal.h"
#include "ETimelineMovementType.generated.h"

UENUM(BlueprintType)
enum class ETimelineMovementType : uint8 {
    Straight,
    Curve,
    SameAsPrevious,
};

