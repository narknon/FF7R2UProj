#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorChickenLureKickExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorChickenLureKickExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorChickenLureKickExtraAction();
};

