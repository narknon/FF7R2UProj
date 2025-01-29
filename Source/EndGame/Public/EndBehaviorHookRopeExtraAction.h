#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorHookRopeExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorHookRopeExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorHookRopeExtraAction();
};

