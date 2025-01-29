#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorSimpleFsmExtraAction.h"
#include "EndBehaviorJumpExtraAction.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBehaviorJumpExtraAction : public FEndBehaviorSimpleFsmExtraAction {
    GENERATED_BODY()
public:
    FEndBehaviorJumpExtraAction();
};

