#pragma once
#include "CoreMinimal.h"
#include "EEndPlayerLeaderActionFlag.generated.h"

UENUM(BlueprintType)
namespace EEndPlayerLeaderActionFlag {
    enum Type {
        IsInJumpAir,
        IsJumpUp,
        IsJumpPosIsFalling,
        Falling,
        Swimming,
        NaviBlockCheckIsSoft,
        FieldDodge,
        FieldDodgeToMove,
        FieldDodgeToFrontJump,
        FieldTargetJump,
        ForceUpdateJumpArrivalPoint,
        IsInWallRunningVolume,
        CanAutoClimbingCatch,
        CanAutoClimbingCatchWithLineCheck,
        DeactiveParamFrame,
        PollingFlagStart,
        PollingFlagCanWallRunning,
        PollingFlagDisableNaturalAction,
        PollingFlagEnd,
        Max,
    };
}

