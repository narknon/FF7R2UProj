#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorSplineMoveExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorSplineMoveExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorSplineMoveExtraAction();
};

