#pragma once
#include "CoreMinimal.h"
#include "EEndEnemyTerritoryState.generated.h"

UENUM(BlueprintType)
enum class EEndEnemyTerritoryState : uint8 {
    None,
    Loading,
    Active,
    Destroying,
    Inactive,
};

