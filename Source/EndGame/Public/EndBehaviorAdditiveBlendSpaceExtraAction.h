#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorAdditiveBlendSpaceExtraAction.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBehaviorAdditiveBlendSpaceExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    FEndBehaviorAdditiveBlendSpaceExtraAction();
};

