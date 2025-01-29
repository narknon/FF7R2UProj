#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorMonkeyBarsExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorMonkeyBarsExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorMonkeyBarsExtraAction();
};

