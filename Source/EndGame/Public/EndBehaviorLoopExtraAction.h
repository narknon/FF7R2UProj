#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorLoopExtraAction.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBehaviorLoopExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    FEndBehaviorLoopExtraAction();
};

