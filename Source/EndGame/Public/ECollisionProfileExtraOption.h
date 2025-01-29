#pragma once
#include "CoreMinimal.h"
#include "ECollisionProfileExtraOption.generated.h"

UENUM(BlueprintType)
enum class ECollisionProfileExtraOption : uint8 {
    Default,
    IgnoreVehicle,
    Max,
};

