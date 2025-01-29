#pragma once
#include "CoreMinimal.h"
#include "EEndHandConstraint.generated.h"

UENUM(BlueprintType)
enum class EEndHandConstraint : uint8 {
    None,
    ManualPlacement,
    ManualTransform,
    LockPlacement,
    LockTransform,
    Trace,
    LockTransformToParentSocket,
    LockTransformToOtherSocket,
    GBike,
};

