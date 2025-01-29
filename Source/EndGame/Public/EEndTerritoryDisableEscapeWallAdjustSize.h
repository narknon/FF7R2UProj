#pragma once
#include "CoreMinimal.h"
#include "EEndTerritoryDisableEscapeWallAdjustSize.generated.h"

UENUM(BlueprintType)
enum class EEndTerritoryDisableEscapeWallAdjustSize : uint8 {
    NoInit,
    TerritorySize,
    ExtendedTerritorySize,
    FreeSize,
};

