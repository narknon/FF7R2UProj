#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorPickupExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorPickupExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorPickupExtraAction();
};

