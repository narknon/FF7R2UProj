#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorMushroomPickingExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorMushroomPickingExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorMushroomPickingExtraAction();
};

