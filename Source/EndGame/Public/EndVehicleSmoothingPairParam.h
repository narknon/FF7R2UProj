#pragma once
#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "EndVehicleSmoothingParam.h"
#include "EndVehicleSmoothingPairParam.generated.h"

USTRUCT(BlueprintType)
struct FEndVehicleSmoothingPairParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRuntimeFloatCurve RateCurve;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndVehicleSmoothingParam SmoothingParamMin;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndVehicleSmoothingParam SmoothingParamMax;
    
    ENDGAME_API FEndVehicleSmoothingPairParam();
};

