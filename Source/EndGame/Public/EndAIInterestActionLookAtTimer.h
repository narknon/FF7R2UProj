#pragma once
#include "CoreMinimal.h"
#include "EndAIInterestActionLookAt.h"
#include "EndAIInterestActionLookAtTimer.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndAIInterestActionLookAtTimer : public FEndAIInterestActionLookAt {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LookAtTime;
    
    FEndAIInterestActionLookAtTimer();
};

