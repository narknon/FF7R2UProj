#pragma once
#include "CoreMinimal.h"
#include "StateConditionParam.generated.h"

USTRUCT(BlueprintType)
struct FStateConditionParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SwapStateConditionNot;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SwapStateCondition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SwapStateChange;
    
    ENDGAME_API FStateConditionParam();
};

