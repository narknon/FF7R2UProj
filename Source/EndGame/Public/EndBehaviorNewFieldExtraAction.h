#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorFieldActionBase.h"
#include "EndBehaviorNewFieldExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorNewFieldExtraAction : public FEndBehaviorFieldActionBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorNewFieldExtraAction();
};

