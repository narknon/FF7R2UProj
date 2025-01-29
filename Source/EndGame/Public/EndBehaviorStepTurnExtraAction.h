#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorStepTurnExtraAction.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBehaviorStepTurnExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    FEndBehaviorStepTurnExtraAction();
};

