#pragma once
#include "CoreMinimal.h"
#include "EAIPCBattleBehavior.generated.h"

UENUM(BlueprintType)
enum class EAIPCBattleBehavior : uint8 {
    eNone,
    eTemp1,
    eBackToBattleArea,
    eCommandExecute,
    eTemp2,
    eToSafeArea,
    eTemp3,
    eConfrontIdle,
    eAvoidDanger,
    eSupportCombination,
    eCombination,
    eBattleLoop,
    eEscaping,
    eMoveBattleArea,
    eNotInBattle,
    eTemp4,
    eExecuteAbility,
    eDoNothing,
    eMax,
};

