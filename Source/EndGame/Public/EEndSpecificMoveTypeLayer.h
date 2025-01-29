#pragma once
#include "CoreMinimal.h"
#include "EEndSpecificMoveTypeLayer.generated.h"

UENUM(BlueprintType)
enum class EEndSpecificMoveTypeLayer : uint8 {
    Debug,
    StateChange,
    ActionPlayerMoveType,
    ActionPlayerAfterGlowMoveType,
    ActionRestrictDashWhenActorsNear,
    ActionAutoWalkType,
    ActionTurnBack,
    LocationVolume,
    RoomBox,
    EnvAttribute,
    Max,
};

