#pragma once
#include "CoreMinimal.h"
#include "EEndTerritoryBattleInAllEnemiesCondition.generated.h"

UENUM(BlueprintType)
enum class EEndTerritoryBattleInAllEnemiesCondition : uint8 {
    OnBattleIn,
    OnTerritoryEnter,
    OnBattleInOld,
    OnCaution,
    None,
};

