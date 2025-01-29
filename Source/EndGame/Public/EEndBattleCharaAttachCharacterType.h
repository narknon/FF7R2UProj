#pragma once
#include "CoreMinimal.h"
#include "EEndBattleCharaAttachCharacterType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleCharaAttachCharacterType : uint8 {
    None,
    LeftArm,
    RightArm,
    BackWeaponTop,
    BackWeaponUnder,
};

