#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorSimpleInteractExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorSimpleInteractExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorSimpleInteractExtraAction();
};

