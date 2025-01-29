#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorFieldCableCartExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorFieldCableCartExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorFieldCableCartExtraAction();
};

