#pragma once
#include "CoreMinimal.h"
#include "EEndCinemaSceneLightCurveApplyType.generated.h"

UENUM(BlueprintType)
enum class EEndCinemaSceneLightCurveApplyType : uint8 {
    Store,
    Addition,
    Multiplication,
};

