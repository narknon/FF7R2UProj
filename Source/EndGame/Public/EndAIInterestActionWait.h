#pragma once
#include "CoreMinimal.h"
#include "EndAIInterestAction.h"
#include "EndAIInterestActionWait.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndAIInterestActionWait : public FEndAIInterestAction {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float WaitTime;
    
    FEndAIInterestActionWait();
};

