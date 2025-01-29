#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorClimbingExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorClimbingExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorClimbingExtraAction();
};

