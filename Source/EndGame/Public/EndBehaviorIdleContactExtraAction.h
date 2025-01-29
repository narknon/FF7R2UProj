#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorContactExtraAction.h"
#include "EndBehaviorIdleContactExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorIdleContactExtraAction : public FEndBehaviorContactExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorIdleContactExtraAction();
};

