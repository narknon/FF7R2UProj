#pragma once
#include "CoreMinimal.h"
#include "EBattleAbilityRotateNotifyState.generated.h"

UENUM(BlueprintType)
namespace EBattleAbilityRotateNotifyState {
    enum Type {
        None,
        Swing,
        TargetPointName,
        TargetLocate,
        ToHorizontalByRoll,
        ToHorizontalByYAxis,
        TargetPointRotation,
    };
}

