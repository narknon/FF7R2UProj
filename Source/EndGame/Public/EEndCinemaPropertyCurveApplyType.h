#pragma once
#include "CoreMinimal.h"
#include "EEndCinemaPropertyCurveApplyType.generated.h"

UENUM(BlueprintType)
enum class EEndCinemaPropertyCurveApplyType : uint8 {
    Store,
    Addition,
    Multiplication,
};

