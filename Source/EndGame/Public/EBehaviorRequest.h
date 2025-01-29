#pragma once
#include "CoreMinimal.h"
#include "EBehaviorRequest.generated.h"

UENUM(BlueprintType)
namespace EBehaviorRequest {
    enum Type {
        eCommandExecute,
        eExecuteAbility,
        eDoNothing,
        eCombination,
        eToSafeArea,
        eAvoidDanger,
        eConfrontIdle,
        eSupportCombination,
        eBackToBattleArea,
        eMax,
    };
}

