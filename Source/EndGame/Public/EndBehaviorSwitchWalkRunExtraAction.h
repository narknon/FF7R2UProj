#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorSequentialExtraAction.h"
#include "EndBehaviorSwitchWalkRunExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorSwitchWalkRunExtraAction : public FEndBehaviorSequentialExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorSwitchWalkRunExtraAction();
};

