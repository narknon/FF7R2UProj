#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorFieldAttackExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorFieldAttackExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorFieldAttackExtraAction();
};

