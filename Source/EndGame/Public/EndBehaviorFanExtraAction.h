#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorFanExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorFanExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorFanExtraAction();
};

