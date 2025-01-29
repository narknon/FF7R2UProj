#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorSlu7pHoldHandsAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorSlu7pHoldHandsAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorSlu7pHoldHandsAction();
};

