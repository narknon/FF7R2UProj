#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorMushroomPickingMushroomExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorMushroomPickingMushroomExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorMushroomPickingMushroomExtraAction();
};

