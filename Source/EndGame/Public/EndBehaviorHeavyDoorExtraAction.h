#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorHeavyDoorExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorHeavyDoorExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorHeavyDoorExtraAction();
};

