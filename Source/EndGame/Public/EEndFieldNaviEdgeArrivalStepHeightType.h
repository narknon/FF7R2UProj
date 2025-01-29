#pragma once
#include "CoreMinimal.h"
#include "EEndFieldNaviEdgeArrivalStepHeightType.generated.h"

UENUM(BlueprintType)
enum class EEndFieldNaviEdgeArrivalStepHeightType : uint8 {
    None,
    UpSkipStep,
    UpSmallStep,
    UpMiddleStep,
    UpBigStep,
    UpHugeStep,
    UpNoStepLow,
    UpNoStepHigh,
    UpWaterStep,
    UpWaterStepHuge,
    UpWaterNoStep,
    DownSkipStep,
    DownSmallStep,
    DownMiddleStep,
    DownBigStep,
    DownHugeStep,
    DownNoStepLow,
    DownNoStepHigh,
    DownWaterStep,
    DownWaterStepHuge,
    DownWaterNoStep,
    DownStartIndex = DownSkipStep,
};

