#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorSpiderMoveExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorSpiderMoveExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorSpiderMoveExtraAction();
};

