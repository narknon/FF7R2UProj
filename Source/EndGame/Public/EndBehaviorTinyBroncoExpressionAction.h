#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorFieldActionBase.h"
#include "EndBehaviorTinyBroncoExpressionAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorTinyBroncoExpressionAction : public FEndBehaviorFieldActionBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorTinyBroncoExpressionAction();
};

