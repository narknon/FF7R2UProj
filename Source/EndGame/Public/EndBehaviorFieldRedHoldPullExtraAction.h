#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldUpperExtraAction.h"
#include "EndBehaviorFieldRedHoldPullExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorFieldRedHoldPullExtraAction : public FEndBehaviorNewFieldUpperExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorFieldRedHoldPullExtraAction();
};

