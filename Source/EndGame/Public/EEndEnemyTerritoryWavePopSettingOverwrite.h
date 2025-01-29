#pragma once
#include "CoreMinimal.h"
#include "EEndEnemyTerritoryWavePopSettingOverwrite.generated.h"

UENUM(BlueprintType)
enum class EEndEnemyTerritoryWavePopSettingOverwrite : uint8 {
    ReinforcementsWavePopType_Default,
    ReinforcementsWavePopType_Closest,
    ReinforcementsWavePopType_Random,
    ReinforcementsWavePopType_Furthest,
    ReinforcementsWavePopType_DirectPoint,
    ReinforcementsWavePopType_OutScreen,
};

