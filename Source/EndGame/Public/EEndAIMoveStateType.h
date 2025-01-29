#pragma once
#include "CoreMinimal.h"
#include "EEndAIMoveStateType.generated.h"

UENUM(BlueprintType)
enum class EEndAIMoveStateType : uint8 {
    None,
    Idle,
    PathFollowing,
    Spline,
    ToAerial,
    JumpGroundToGround,
    JumpGroundToWall,
    AerialIdle,
    AerialPathFollowing,
    AerialSpline,
    AerialToGround,
    JumpAerialToGround,
    JumpAerialToWall,
    WallIdle,
    WallPathFollowing,
    JumpWallToGround,
    JumpWallToWall,
};

