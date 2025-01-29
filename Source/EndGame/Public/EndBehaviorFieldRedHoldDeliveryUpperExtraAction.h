#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldUpperExtraAction.h"
#include "EndBehaviorFieldRedHoldDeliveryUpperExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorFieldRedHoldDeliveryUpperExtraAction : public FEndBehaviorNewFieldUpperExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorFieldRedHoldDeliveryUpperExtraAction();
};

