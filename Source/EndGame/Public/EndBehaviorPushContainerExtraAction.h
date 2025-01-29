#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorPushContainerExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorPushContainerExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorPushContainerExtraAction();
};

