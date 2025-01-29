#pragma once
#include "CoreMinimal.h"
#include "EndAnimationSettingsMovementExpression.generated.h"

USTRUCT(BlueprintType)
struct FEndAnimationSettingsMovementExpression {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float InputBaseAngleRateNeutral;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float InputBaseAngleRateRatioBattle;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DefaultRotationInterpSpeed;
    
    ENDGAME_API FEndAnimationSettingsMovementExpression();
};

