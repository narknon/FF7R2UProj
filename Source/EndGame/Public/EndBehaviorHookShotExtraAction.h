#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorHookShotExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorHookShotExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorHookShotExtraAction();
};

