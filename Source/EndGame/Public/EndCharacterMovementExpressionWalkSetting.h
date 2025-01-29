#pragma once
#include "CoreMinimal.h"
#include "EndCharacterMovementExpressionBoneSetting.h"
#include "EndCharacterMovementExpressionWalkSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndCharacterMovementExpressionWalkSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndCharacterMovementExpressionBoneSetting> BoneSettings;
    
    ENDGAME_API FEndCharacterMovementExpressionWalkSetting();
};

