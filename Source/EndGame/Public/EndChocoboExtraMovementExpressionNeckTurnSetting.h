#pragma once
#include "CoreMinimal.h"
#include "EndChocoboExtraMovementExpressionNeckTurnSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndChocoboExtraMovementExpressionNeckTurnSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float NeckTurnIncrease;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float NeckTurnDecrease;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float NeckTurnInterpSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float NeckTurnDecreaseInterpSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MaxNeckTurnAngle;
    
    ENDGAME_API FEndChocoboExtraMovementExpressionNeckTurnSetting();
};

