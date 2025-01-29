#pragma once
#include "CoreMinimal.h"
#include "EEndAIInterestActionTag.h"
#include "EndAIInterestAction.h"
#include "EndAIInterestActionManual.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndAIInterestActionManual : public FEndAIInterestAction {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    EEndAIInterestActionTag BehaviorTag;
    
    FEndAIInterestActionManual();
};

