#pragma once
#include "CoreMinimal.h"
#include "EEndEquipmentUniqueActionType.generated.h"

UENUM(BlueprintType)
enum class EEndEquipmentUniqueActionType : uint8 {
    None,
    OffensiveModeChange,
    BuffLevelDownAbility,
    ChargeAbility,
    EnergyAbility,
    Ability,
    DistanceAbility,
    Revenge,
    Derived,
    Tension,
};

