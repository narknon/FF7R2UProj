#pragma once
#include "CoreMinimal.h"
#include "EEndTerritoryAreaCheckCondition.generated.h"

UENUM(BlueprintType)
enum class EEndTerritoryAreaCheckCondition : uint8 {
    Territory,
    ExtendedTerritory,
    FreeBattleArea,
    None,
};

