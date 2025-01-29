#pragma once
#include "CoreMinimal.h"
#include "EndBikeExpressionWindParameters.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBikeExpressionWindParameters {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableWindExpression;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float WindSpeedRate;
    
    FEndBikeExpressionWindParameters();
};

