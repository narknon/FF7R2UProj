#pragma once
#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "EndVehicleRangedCurveParam.generated.h"

USTRUCT(BlueprintType)
struct FEndVehicleRangedCurveParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRuntimeFloatCurve ValueCurve;
    
    ENDGAME_API FEndVehicleRangedCurveParam();
};

