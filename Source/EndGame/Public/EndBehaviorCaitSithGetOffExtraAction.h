#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorCaitSithGetOffExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorCaitSithGetOffExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorCaitSithGetOffExtraAction();
};

