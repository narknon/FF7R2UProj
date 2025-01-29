#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorFieldActionBase.h"
#include "EndBehaviorCrackExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorCrackExtraAction : public FEndBehaviorFieldActionBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorCrackExtraAction();
};

