#pragma once
#include "CoreMinimal.h"
#include "EndBattleAbilityCancelComboCondition.generated.h"

UENUM(BlueprintType)
enum class EndBattleAbilityCancelComboCondition : uint8 {
    None,
    SelfBuff,
    OffensiveMode,
};

