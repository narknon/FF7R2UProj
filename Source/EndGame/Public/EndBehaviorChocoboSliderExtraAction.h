#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorFieldActionBase.h"
#include "EndBehaviorChocoboSliderExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorChocoboSliderExtraAction : public FEndBehaviorFieldActionBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorChocoboSliderExtraAction();
};

