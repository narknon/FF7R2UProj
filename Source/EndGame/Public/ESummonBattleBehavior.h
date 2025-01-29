#pragma once
#include "CoreMinimal.h"
#include "ESummonBattleBehavior.generated.h"

UENUM(BlueprintType)
enum class ESummonBattleBehavior : uint8 {
    eAppear,
    eReadyToFight,
    eBattleLoop,
    eCommandExecute,
    eHide,
    eResetLocation,
    eReturn,
    eDoNothing,
    eAcceptingCommands,
    eMoveToAnother,
};

