#pragma once
#include "CoreMinimal.h"
#include "EEndBattlePlayerUniqueAbilityType.generated.h"

UENUM(BlueprintType)
enum class EEndBattlePlayerUniqueAbilityType : uint8 {
    None,
    OffensiveMode,
    Energy,
    SelfBuff,
    CoolDownTime,
    Revenge,
    ThrowWeapon,
    Derived,
    FatMoogle,
    Tension,
};

