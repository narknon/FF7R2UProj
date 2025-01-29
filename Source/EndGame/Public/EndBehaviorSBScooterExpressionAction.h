#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorFieldActionBase.h"
#include "EndBehaviorSBScooterExpressionAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorSBScooterExpressionAction : public FEndBehaviorFieldActionBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorSBScooterExpressionAction();
};

