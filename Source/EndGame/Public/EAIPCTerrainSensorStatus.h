#pragma once
#include "CoreMinimal.h"
#include "EAIPCTerrainSensorStatus.generated.h"

UENUM(BlueprintType)
enum class EAIPCTerrainSensorStatus : uint8 {
    Normal,
    NearWall,
    Narrow,
};

