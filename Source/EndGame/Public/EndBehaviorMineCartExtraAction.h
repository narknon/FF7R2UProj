#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorMineCartExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorMineCartExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorMineCartExtraAction();
};

