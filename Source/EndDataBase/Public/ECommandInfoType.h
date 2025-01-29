#pragma once
#include "CoreMinimal.h"
#include "ECommandInfoType.generated.h"

UENUM(BlueprintType)
enum class ECommandInfoType : uint8 {
    BASE,
    MAGIC_ABILITY,
    MUG_ABILITY,
    WEAPON_ABILITY,
    CHARACTER_ABILITY,
};

