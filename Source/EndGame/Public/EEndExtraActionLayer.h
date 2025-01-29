#pragma once
#include "CoreMinimal.h"
#include "EEndExtraActionLayer.generated.h"

UENUM(BlueprintType)
enum class EEndExtraActionLayer : uint8 {
    HighPriority,
    Default,
    LowPriority,
    Max,
};

