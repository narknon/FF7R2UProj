#pragma once
#include "CoreMinimal.h"
#include "EEndDashType.generated.h"

UENUM(BlueprintType)
enum class EEndDashType : uint8 {
    Enable,
    Disable,
    SpecificMoveDash,
    Max,
};

