#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorMuscleMiniGameAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorMuscleMiniGameAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorMuscleMiniGameAction();
};

