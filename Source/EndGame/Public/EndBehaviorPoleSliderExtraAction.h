#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorFieldActionBase.h"
#include "EndBehaviorPoleSliderExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorPoleSliderExtraAction : public FEndBehaviorFieldActionBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorPoleSliderExtraAction();
};

