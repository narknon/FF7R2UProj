#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorHandlePuzzlePlayerExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorHandlePuzzlePlayerExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorHandlePuzzlePlayerExtraAction();
};

