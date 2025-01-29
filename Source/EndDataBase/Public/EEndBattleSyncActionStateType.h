#pragma once
#include "CoreMinimal.h"
#include "EEndBattleSyncActionStateType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleSyncActionStateType : uint8 {
    Begin,
    BeginRightHand,
    BeginLeftHand,
    Loop,
    EndFailure,
    EndSuccessByOthers,
    EndTargetDead,
    End,
    EndRightHand,
    EndLeftHand,
    EndEnableWalk,
};

