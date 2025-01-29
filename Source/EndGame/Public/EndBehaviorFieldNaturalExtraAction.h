#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorFieldNaturalExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorFieldNaturalExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorFieldNaturalExtraAction();
};

