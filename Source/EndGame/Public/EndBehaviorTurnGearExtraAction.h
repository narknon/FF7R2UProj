#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorTurnGearExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorTurnGearExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorTurnGearExtraAction();
};

