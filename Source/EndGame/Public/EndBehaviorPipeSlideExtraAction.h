#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorFieldActionBase.h"
#include "EndBehaviorPipeSlideExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorPipeSlideExtraAction : public FEndBehaviorFieldActionBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorPipeSlideExtraAction();
};

