#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorFieldActionBase.h"
#include "EndBehaviorCrouchedExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorCrouchedExtraAction : public FEndBehaviorFieldActionBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorCrouchedExtraAction();
};

