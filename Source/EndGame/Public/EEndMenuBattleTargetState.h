#pragma once
#include "CoreMinimal.h"
#include "EEndMenuBattleTargetState.generated.h"

UENUM(BlueprintType)
enum class EEndMenuBattleTargetState : uint8 {
    None,
    Enabled,
    Disabled,
    LockedEnabled,
    LockedDisabled,
    OutEnabled,
    OutDisabled,
    OutLockedEnabled,
    OutLockedDisabled,
};

