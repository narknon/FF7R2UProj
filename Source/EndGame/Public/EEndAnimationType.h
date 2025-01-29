#pragma once
#include "CoreMinimal.h"
#include "EEndAnimationType.generated.h"

UENUM(BlueprintType)
enum class EEndAnimationType : uint8 {
    BodySequence,
    BodyBlendSpace,
    AdditiveSequence,
    AdditiveBlendSpace,
};

