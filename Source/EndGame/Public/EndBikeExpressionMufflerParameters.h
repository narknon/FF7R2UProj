#pragma once
#include "CoreMinimal.h"
#include "EEndBikeBones.h"
#include "EndBikeExpressionMufflerParameters.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBikeExpressionMufflerParameters {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableMufflerVibration;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndBikeBones MufflerBoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float VibrationRate;
    
    FEndBikeExpressionMufflerParameters();
};

