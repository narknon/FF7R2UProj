#pragma once
#include "CoreMinimal.h"
#include "EEndAiBattleTargetType.generated.h"

UENUM(BlueprintType)
namespace EEndAiBattleTargetType {
    enum Type {
        Own,
        Target,
        Party,
        Enemy,
        Guest,
        Ucpc,
        All,
    };
}

