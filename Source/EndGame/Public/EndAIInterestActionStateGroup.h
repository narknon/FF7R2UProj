#pragma once
#include "CoreMinimal.h"
#include "EndAIInterestAction.h"
#include "EndAIInterestActionStateGroup.generated.h"

USTRUCT(BlueprintType)
struct FEndAIInterestActionStateGroup : public FEndAIInterestAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndAIInterestActionStateGroup();
};

