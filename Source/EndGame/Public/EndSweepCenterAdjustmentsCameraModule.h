#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndSweepCenterAdjustmentsCameraModule.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndSweepCenterAdjustmentsCameraModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    FEndSweepCenterAdjustmentsCameraModule();
};

