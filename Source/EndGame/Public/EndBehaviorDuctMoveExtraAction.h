#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorDuctMoveExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorDuctMoveExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorDuctMoveExtraAction();
};

