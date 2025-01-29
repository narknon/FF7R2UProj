#pragma once
#include "CoreMinimal.h"
#include "EEndEnemyTerritoryShape.generated.h"

UENUM(BlueprintType)
enum class EEndEnemyTerritoryShape : uint8 {
    None,
    Cylinder,
    Cube,
    Cone,
};

