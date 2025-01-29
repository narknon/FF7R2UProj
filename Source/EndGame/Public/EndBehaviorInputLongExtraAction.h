#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorNewFieldExtraAction.h"
#include "EndBehaviorInputLongExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorInputLongExtraAction : public FEndBehaviorNewFieldExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorInputLongExtraAction();
};

