#pragma once
#include "CoreMinimal.h"
#include "EndVehicleSmoothingParam.h"
#include "EndBikeSettingSmootingParam.generated.h"

USTRUCT(BlueprintType)
struct FEndBikeSettingSmootingParam : public FEndVehicleSmoothingParam {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBikeSettingSmootingParam();
};

