#pragma once
#include "CoreMinimal.h"
#include "EAutoWeaponAbilitySpecialCaseType.generated.h"

UENUM(BlueprintType)
enum class EAutoWeaponAbilitySpecialCaseType : uint8 {
    None,
    OverrideGuard,
    Toad,
    OverrideDodge = 4,
    BoundTick = 8,
    BoundSyncAction = 16,
    CancelCombo = 32,
    CounterAbility = 64,
    Aerial = 128,
};

