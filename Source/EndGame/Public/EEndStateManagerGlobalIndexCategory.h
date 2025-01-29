#pragma once
#include "CoreMinimal.h"
#include "EEndStateManagerGlobalIndexCategory.generated.h"

UENUM(BlueprintType)
enum class EEndStateManagerGlobalIndexCategory : uint8 {
    None,
    EnemyTerritory,
    EnemyWave,
    NPCMob,
    Max,
};

