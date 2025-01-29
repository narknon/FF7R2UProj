#pragma once
#include "CoreMinimal.h"
#include "EndCharacterMovementExpressionWalkSetting.h"
#include "EndCharacterMovementExpressionBehaviorSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndCharacterMovementExpressionBehaviorSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCharacterMovementExpressionWalkSetting Walk;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCharacterMovementExpressionWalkSetting Run;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCharacterMovementExpressionWalkSetting Dash;
    
    ENDGAME_API FEndCharacterMovementExpressionBehaviorSetting();
};

