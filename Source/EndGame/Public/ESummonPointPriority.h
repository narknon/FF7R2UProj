#pragma once
#include "CoreMinimal.h"
#include "ESummonPointPriority.generated.h"

UENUM(BlueprintType)
enum class ESummonPointPriority : uint8 {
    Low,
    Normal,
    High,
};

