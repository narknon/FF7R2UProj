#pragma once
#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "EndBikeSettingCurveRateParam.generated.h"

USTRUCT(BlueprintType)
struct FEndBikeSettingCurveRateParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MaxValue;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRuntimeFloatCurve ValueRateCurve;
    
    ENDGAME_API FEndBikeSettingCurveRateParam();
};

