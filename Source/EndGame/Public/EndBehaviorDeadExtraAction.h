#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorSimpleFsmExtraAction.h"
#include "EndBehaviorDeadExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorDeadExtraAction : public FEndBehaviorSimpleFsmExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorDeadExtraAction();
};

