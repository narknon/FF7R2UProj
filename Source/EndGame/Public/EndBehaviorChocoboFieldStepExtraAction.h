#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorFieldActionBase.h"
#include "EndBehaviorChocoboFieldStepExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorChocoboFieldStepExtraAction : public FEndBehaviorFieldActionBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorChocoboFieldStepExtraAction();
};

