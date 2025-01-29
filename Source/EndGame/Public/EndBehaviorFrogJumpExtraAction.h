#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorFrogJumpExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorFrogJumpExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorFrogJumpExtraAction();
};

