#pragma once
#include "CoreMinimal.h"
#include "EndCharacterMovementExpressionBehaviorSetting.h"
#include "EndCharacterMovementExpressionSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndCharacterMovementExpressionSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCharacterMovementExpressionBehaviorSetting Neutral;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCharacterMovementExpressionBehaviorSetting Battle;
    
    ENDGAME_API FEndCharacterMovementExpressionSetting();
};

