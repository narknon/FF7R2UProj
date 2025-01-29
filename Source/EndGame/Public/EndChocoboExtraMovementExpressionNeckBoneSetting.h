#pragma once
#include "CoreMinimal.h"
#include "EndChocoboExtraMovementExpressionNeckBoneSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndChocoboExtraMovementExpressionNeckBoneSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName BoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BoneTurnRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BoneInterpSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bReverseRoll;
    
    ENDGAME_API FEndChocoboExtraMovementExpressionNeckBoneSetting();
};

