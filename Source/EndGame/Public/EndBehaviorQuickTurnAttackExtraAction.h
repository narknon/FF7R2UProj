#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorBattleAbilityExtraAction.h"
#include "EndBehaviorQuickTurnAttackExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorQuickTurnAttackExtraAction : public FEndBehaviorBattleAbilityExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorQuickTurnAttackExtraAction();
};

