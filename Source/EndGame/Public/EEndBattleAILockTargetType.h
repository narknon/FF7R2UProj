#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAILockTargetType.generated.h"

UENUM()
enum class EEndBattleAILockTargetType {
    None = -1,
    Dispersion = 0,
    LockGroupWeak,
    BluePrint,
    AbilityLockLine,
    AbilityLock,
    AbilityLockCheck,
    HateLockLine,
    LockGroupStrong,
    ForceLock,
    ForceLockCheck,
    Max,
};

