#pragma once
#include "CoreMinimal.h"
#include "EForceEnableOverlapMask.generated.h"

UENUM(BlueprintType)
enum class EForceEnableOverlapMask : uint8 {
    Default,
    Vehicle,
    Max,
};

