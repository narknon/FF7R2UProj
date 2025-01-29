#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorCutSeamlessInExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorCutSeamlessInExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorCutSeamlessInExtraAction();
};

