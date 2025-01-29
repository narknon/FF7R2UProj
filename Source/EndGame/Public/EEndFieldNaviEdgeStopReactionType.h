#pragma once
#include "CoreMinimal.h"
#include "EEndFieldNaviEdgeStopReactionType.generated.h"

UENUM()
enum class EEndFieldNaviEdgeStopReactionType : int32 {
    None,
    DownStepBig,
    DownStepHuge,
    DownNoStepHigh,
    AutoFall,
    AutoJump,
    AutoSkip,
};

