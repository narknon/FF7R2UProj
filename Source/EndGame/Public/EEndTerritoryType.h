#pragma once
#include "CoreMinimal.h"
#include "EEndTerritoryType.generated.h"

UENUM(BlueprintType)
enum class EEndTerritoryType : uint8 {
    Mob,
    Patrol,
    ExternalEnemies,
    Boss,
    Dummy,
};

