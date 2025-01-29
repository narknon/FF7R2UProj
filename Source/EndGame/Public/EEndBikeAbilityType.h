#pragma once
#include "CoreMinimal.h"
#include "EEndBikeAbilityType.generated.h"

UENUM(BlueprintType)
enum class EEndBikeAbilityType : uint8 {
    None,
    PlayerNormal,
    PlayerATB,
    PlayerLimit,
    EnemyNormal = 10,
    EnemySpecial,
};

