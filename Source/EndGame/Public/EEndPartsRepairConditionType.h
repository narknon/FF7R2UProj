#pragma once
#include "CoreMinimal.h"
#include "EEndPartsRepairConditionType.generated.h"

UENUM(BlueprintType)
enum class EEndPartsRepairConditionType : uint8 {
    Default,
    UnbrokenPartsFullRecovery,
};

