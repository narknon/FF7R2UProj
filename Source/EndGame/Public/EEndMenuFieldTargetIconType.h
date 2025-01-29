#pragma once
#include "CoreMinimal.h"
#include "EEndMenuFieldTargetIconType.generated.h"

UENUM(BlueprintType)
enum class EEndMenuFieldTargetIconType : uint8 {
    Triangle,
    Square,
    R1,
    Circle,
    R2,
    L1,
    L2,
    LStickTurn,
    Max,
};

