#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorTreasureExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorTreasureExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorTreasureExtraAction();
};

