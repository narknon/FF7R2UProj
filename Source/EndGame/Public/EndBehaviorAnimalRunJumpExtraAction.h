#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorJumpExtraAction.h"
#include "EndBehaviorAnimalRunJumpExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorAnimalRunJumpExtraAction : public FEndBehaviorJumpExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorAnimalRunJumpExtraAction();
};

