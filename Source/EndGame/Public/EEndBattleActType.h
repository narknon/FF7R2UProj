#pragma once
#include "CoreMinimal.h"
#include "EEndBattleActType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleActType : uint8 {
    Move,
    Moves,
    Turn,
    Warp,
    Motion,
    MotionEnd,
    ActMax,
};

