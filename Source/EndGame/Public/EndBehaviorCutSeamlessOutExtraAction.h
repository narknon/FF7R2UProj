#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorCutSeamlessOutExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorCutSeamlessOutExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorCutSeamlessOutExtraAction();
};

