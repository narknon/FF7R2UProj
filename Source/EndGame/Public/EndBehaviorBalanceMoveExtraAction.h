#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorBalanceMoveExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorBalanceMoveExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorBalanceMoveExtraAction();
};

