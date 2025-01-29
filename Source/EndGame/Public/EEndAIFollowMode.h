#pragma once
#include "CoreMinimal.h"
#include "EEndAIFollowMode.generated.h"

UENUM(BlueprintType)
enum class EEndAIFollowMode : uint8 {
    Normal,
    NormalWait,
    PointLeave,
    PointLeaveWait,
    BackwardLeaveLeaderToPoint,
    GlideJumpAreaLeave,
    GlideTeleport,
    Glide,
    JetMoveToStartPosition,
    JetTeleport,
    Jet,
};

