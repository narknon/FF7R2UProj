#pragma once
#include "CoreMinimal.h"
#include "EndAIInterestAction.h"
#include "EndAIInterestActionPlayVoice.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndAIInterestActionPlayVoice : public FEndAIInterestAction {
    GENERATED_BODY()
public:
    FEndAIInterestActionPlayVoice();
};

