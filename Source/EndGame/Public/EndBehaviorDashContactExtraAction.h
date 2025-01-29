#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorRunContactExtraAction.h"
#include "EndBehaviorDashContactExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorDashContactExtraAction : public FEndBehaviorRunContactExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorDashContactExtraAction();
};

