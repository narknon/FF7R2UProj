#pragma once
#include "CoreMinimal.h"
#include "EWeaponCoreAutoSettingType.generated.h"

UENUM(BlueprintType)
enum class EWeaponCoreAutoSettingType : uint8 {
    NONE,
    BALANCE,
    ATTACK,
    DEFENSE,
    MAX,
};

