#pragma once
#include "CoreMinimal.h"
#include "EndAIInterestAction.h"
#include "EndAIInterestActionOverrideIdleVariation.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndAIInterestActionOverrideIdleVariation : public FEndAIInterestAction {
    GENERATED_BODY()
public:
    FEndAIInterestActionOverrideIdleVariation();
};

