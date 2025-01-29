#pragma once
#include "CoreMinimal.h"
#include "EWeaponSlot.generated.h"

UENUM(BlueprintType)
enum class EWeaponSlot : uint8 {
    EWeaponSlot_1,
    EWeaponSlot_2,
    EWeaponSlot_3,
    EWeaponSlot_4,
    EWeaponSlot_5,
    EWeaponSlot_6,
    EWeaponSlot_7,
    EWeaponSlot_8,
    EWeaponSlot_9,
    EWeaponSlot_10,
    EWeaponSlot_MAX UMETA(Hidden),
    EWeaponSlot_NONE,
};

