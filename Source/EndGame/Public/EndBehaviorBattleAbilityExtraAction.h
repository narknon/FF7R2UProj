#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorBattleAbilityExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorBattleAbilityExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorBattleAbilityExtraAction();
};

