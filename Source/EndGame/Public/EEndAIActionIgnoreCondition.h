#pragma once
#include "CoreMinimal.h"
#include "EEndAIActionIgnoreCondition.generated.h"

UENUM(BlueprintType)
enum class EEndAIActionIgnoreCondition : uint8 {
    None,
    All,
    Distance,
    DistanceMin,
    DistanceMax,
    Height,
    AngleYaw,
    AnglePitch,
    CoolTime,
};

