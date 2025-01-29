#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAbilityMoveWeaponRelativeToTargetType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleAbilityMoveWeaponRelativeToTargetType : uint8 {
    Toward,
    Stay,
    Return,
};

