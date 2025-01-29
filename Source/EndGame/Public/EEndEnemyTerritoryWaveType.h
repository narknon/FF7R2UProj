#pragma once
#include "CoreMinimal.h"
#include "EEndEnemyTerritoryWaveType.generated.h"

UENUM(BlueprintType)
enum class EEndEnemyTerritoryWaveType : uint8 {
    ReinforcementsWaveType_Next,
    ReinforcementsWaveType_Direct,
    ReinforcementsWaveType_Random,
};

