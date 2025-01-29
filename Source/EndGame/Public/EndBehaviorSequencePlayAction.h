#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorAction.h"
#include "EndBehaviorSequencePlayAction.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBehaviorSequencePlayAction : public FEndBehaviorAction {
    GENERATED_BODY()
public:
    FEndBehaviorSequencePlayAction();
};

