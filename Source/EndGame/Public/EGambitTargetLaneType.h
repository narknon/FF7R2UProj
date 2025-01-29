#pragma once
#include "CoreMinimal.h"
#include "EGambitTargetLaneType.generated.h"

UENUM(BlueprintType)
enum class EGambitTargetLaneType : uint8 {
    None,
    Lane1,
    Lane2,
    Lane3,
    GeneratedLane,
    GeneratedLaneOrNeedTarget,
    TheMostRobots,
    TheLatestEnemyDead,
};

