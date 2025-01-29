#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorChocoboStopExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorChocoboStopExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorChocoboStopExtraAction();
};

