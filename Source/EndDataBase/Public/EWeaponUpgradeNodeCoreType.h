#pragma once
#include "CoreMinimal.h"
#include "EWeaponUpgradeNodeCoreType.generated.h"

UENUM()
enum class EWeaponUpgradeNodeCoreType : uint8 {
    MAINCORE = 1,
    SUBCORE,
    SKILLCORE,
    PARAMCORE,
    NONE = 0,
    MAX = NONE,
};

