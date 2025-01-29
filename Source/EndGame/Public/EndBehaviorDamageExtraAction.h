#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorDamageExtraAction.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBehaviorDamageExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    FEndBehaviorDamageExtraAction();
};

