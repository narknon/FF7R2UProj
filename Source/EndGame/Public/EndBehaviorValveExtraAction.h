#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorValveExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorValveExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorValveExtraAction();
};

