#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorFieldSplineMoveExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorFieldSplineMoveExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorFieldSplineMoveExtraAction();
};

