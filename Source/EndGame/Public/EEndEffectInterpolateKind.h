#pragma once
#include "CoreMinimal.h"
#include "EEndEffectInterpolateKind.generated.h"

UENUM(BlueprintType)
enum class EEndEffectInterpolateKind : uint8 {
    Linear,
    EaseInOut,
};

