#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorModifyTransformExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorModifyTransformExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorModifyTransformExtraAction();
};

