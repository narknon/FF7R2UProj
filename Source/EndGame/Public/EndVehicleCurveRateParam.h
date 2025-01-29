#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Curves/CurveFloat.h"
#include "EndVehicleCurveRateParam.generated.h"

USTRUCT(BlueprintType)
struct FEndVehicleCurveRateParam {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FFloatInterval Interval;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRuntimeFloatCurve RateCurve;
    
    ENDGAME_API FEndVehicleCurveRateParam();
};

