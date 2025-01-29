#pragma once
#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "EndBikeSettingSmootingParam.h"
#include "EndBikeSettingSmoothingPairParam.generated.h"

USTRUCT(BlueprintType)
struct FEndBikeSettingSmoothingPairParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRuntimeFloatCurve InputCurve;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndBikeSettingSmootingParam SmoothingParamMin;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndBikeSettingSmootingParam SmoothingParamMax;
    
    ENDGAME_API FEndBikeSettingSmoothingPairParam();
};

