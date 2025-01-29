#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorFieldActionBase.h"
#include "EndBehaviorFieldCableCatchExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorFieldCableCatchExtraAction : public FEndBehaviorFieldActionBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorFieldCableCatchExtraAction();
};

