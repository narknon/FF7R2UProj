#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorSequentialExtraAction.h"
#include "EndBehaviorSwitchBehaviorExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorSwitchBehaviorExtraAction : public FEndBehaviorSequentialExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorSwitchBehaviorExtraAction();
};

