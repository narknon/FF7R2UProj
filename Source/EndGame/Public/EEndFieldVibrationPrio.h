#pragma once
#include "CoreMinimal.h"
#include "EEndFieldVibrationPrio.generated.h"

UENUM(BlueprintType)
enum class EEndFieldVibrationPrio : uint8 {
    VIB_OneShotHigh,
    VIB_LoopHigh,
    VIB_OneShotNormal,
    VIB_LoopNormal,
    VIB_OneShotLow,
    VIB_LoopLow,
};

