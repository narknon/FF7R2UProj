#pragma once
#include "CoreMinimal.h"
#include "EEndWeaponUpgradeKind.generated.h"

UENUM(BlueprintType)
enum class EEndWeaponUpgradeKind : uint8 {
    UnKnown = 255,
    Core = 0,
    Skill,
    Upgrade,
    MaxUpgrade = Skill,
    MaxMainCoreResource = 4,
    MaxSubCoreResource = MaxMainCoreResource,
};

