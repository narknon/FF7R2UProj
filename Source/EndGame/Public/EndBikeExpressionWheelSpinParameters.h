#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EEndBikeBones.h"
#include "EndBikeExpressionWheelSpinParameters.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBikeExpressionWheelSpinParameters {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableWheelSpin;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndBikeBones WheelBoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRotator RotationRate;
    
    FEndBikeExpressionWheelSpinParameters();
};

