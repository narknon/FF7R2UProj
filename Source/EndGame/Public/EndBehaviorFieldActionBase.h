#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorFieldActionBase.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorFieldActionBase : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorFieldActionBase();
};

