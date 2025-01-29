#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorFieldActionBase.h"
#include "EndBehaviorFieldActionCustomExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorFieldActionCustomExtraAction : public FEndBehaviorFieldActionBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorFieldActionCustomExtraAction();
};

