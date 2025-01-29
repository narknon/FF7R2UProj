#pragma once
#include "CoreMinimal.h"
#include "EEndAIMoveDefinition.generated.h"

UENUM(BlueprintType)
enum class EEndAIMoveDefinition : uint8 {
    Empty,
    Confront,
    ConfrontAir,
    ConfrontTwoStageToAction,
    Around,
    AroundAir,
    AroundAirTargetCross,
    AroundNoSwitchDirc,
    AroundSpecialStandby,
    Step,
    OneWay,
    FastDash,
    MoveToMultiPoint,
    MoveToNearTheGroupMember,
    Jump,
    Warp,
    WarpToNearTheTarget,
    MoveToGroupOffset,
    Herd,
    HerdAir,
    ZigzagStep,
    TakeoffAndLanding,
    WaveAttackMember,
    EB2000_GroundToCeiling,
    EB2090_ShieldingMove,
    EN0007_WallMove,
    Max,
};

