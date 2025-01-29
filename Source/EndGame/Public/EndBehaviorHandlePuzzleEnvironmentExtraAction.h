#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorHandlePuzzleEnvironmentExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorHandlePuzzleEnvironmentExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorHandlePuzzleEnvironmentExtraAction();
};

