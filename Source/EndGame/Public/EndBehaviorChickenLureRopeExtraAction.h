#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorChickenLureRopeExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorChickenLureRopeExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorChickenLureRopeExtraAction();
};

