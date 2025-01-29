#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorHoldObjectExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorHoldObjectExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorHoldObjectExtraAction();
};

