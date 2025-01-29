#pragma once
#include "CoreMinimal.h"
#include "EEndBattleDamageSourceHitReactionType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleDamageSourceHitReactionType : uint8 {
    None = 2,
    Small = 0,
    Medium = 8,
    Large = 1,
    LaunchSmall = 3,
    LaunchLarge = 9,
    BlowSmall = 4,
    BlowLarge = 10,
    Strike = 5,
    SyncAction,
    Motion,
    Add = 11,
    Repel,
    AerialDeadLaunchLarge,
    AerialDeadBlowLarge,
    AerialDeadStrike,
    AerialSuspendActionLaunchLarge,
    BurstPushBlowLarge,
    FallDown,
    MotionBeginLoopEnd,
    MotionBeginLoopEndDamageHitProcessTimeLoopEnd = 23,
    DownHit = 20,
    PullBlow,
    PullMedium,
    Max = MotionBeginLoopEndDamageHitProcessTimeLoopEnd,
};

