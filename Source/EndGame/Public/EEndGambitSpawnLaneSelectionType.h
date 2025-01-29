#pragma once
#include "CoreMinimal.h"
#include "EEndGambitSpawnLaneSelectionType.generated.h"

UENUM(BlueprintType)
enum class EEndGambitSpawnLaneSelectionType : uint8 {
    Spawn_Here,
    Spawn_LaneManyRobot,
    Spawn_LaneLessRobot,
    Spawn_LaneHighHPFactory,
    Spawn_LaneLowHPFactory,
};

