#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorFieldActionBase.h"
#include "EndBehaviorSwimmingSnapExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorSwimmingSnapExtraAction : public FEndBehaviorFieldActionBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorSwimmingSnapExtraAction();
};

