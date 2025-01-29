#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorKnockBackExtraAction.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBehaviorKnockBackExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    FEndBehaviorKnockBackExtraAction();
};

