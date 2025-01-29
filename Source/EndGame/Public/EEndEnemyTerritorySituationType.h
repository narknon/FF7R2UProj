#pragma once
#include "CoreMinimal.h"
#include "EEndEnemyTerritorySituationType.generated.h"

UENUM(BlueprintType)
enum class EEndEnemyTerritorySituationType : uint8 {
    None,
    Event,
    Serious,
};

