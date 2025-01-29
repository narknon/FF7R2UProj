#pragma once
#include "CoreMinimal.h"
#include "EEndAIBattleEvacuationRole.generated.h"

UENUM(BlueprintType)
enum class EEndAIBattleEvacuationRole : uint8 {
    None,
    BattleMain,
    BattleSubStart,
    BattleSub1 = BattleSubStart,
    BattleSub2,
    BattleSub3,
    BattleSub4,
    BattleSub5,
    BattleSubEnd,
    FieldMain,
    FieldSubStart,
    FieldSub1 = FieldSubStart,
    FieldSub2,
    FieldSubEnd,
};

