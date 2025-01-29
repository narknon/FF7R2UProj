#pragma once
#include "CoreMinimal.h"
#include "EEndBikeBones.h"
#include "EndBikeExpressionWheelAxleParameters.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBikeExpressionWheelAxleParameters {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableWheelAxleExpression;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndBikeBones LeftWheelBoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndBikeBones RightWheelBoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TiltRate;
    
    FEndBikeExpressionWheelAxleParameters();
};

