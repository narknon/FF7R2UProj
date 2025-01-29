#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorFieldDodgeExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorFieldDodgeExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorFieldDodgeExtraAction();
};

