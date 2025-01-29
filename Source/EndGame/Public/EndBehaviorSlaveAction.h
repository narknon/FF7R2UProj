#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorSequencePlayAction.h"
#include "EndBehaviorSlaveAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorSlaveAction : public FEndBehaviorSequencePlayAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorSlaveAction();
};

