#pragma once
#include "CoreMinimal.h"
#include "eEndBattleDamageSourceHitReactionType_BD.generated.h"

UENUM(BlueprintType)
enum eEndBattleDamageSourceHitReactionType_BD {
    None_BD = 2,
    Small_BD = 0,
    Medium_BD = 8,
    Large_BD = 1,
    LaunchSmall_BD = 3,
    LaunchLarge_BD = 9,
    BlowSmall_BD = 4,
    BlowLarge_BD = 10,
    Strike_BD = 5,
    SyncAction_BD,
    Motion_BD,
    Add_BD = 11,
    Repel_BD,
    AerialDeadLaunchLarge_BD,
    AerialDeadBlowLarge_BD,
    AerialDeadStrike_BD,
    AerialSuspendActionLaunchLarge_BD,
    BurstPushBlowLarge_BD,
    FallDown_BD,
    MotionBeginLoopEnd_BD,
    MotionBeginLoopEndDamageHitProcessTimeLoopEnd_BD = 23,
    DownHit_BD = 20,
    PullBlow_BD,
    PullMedium_BD,
};

