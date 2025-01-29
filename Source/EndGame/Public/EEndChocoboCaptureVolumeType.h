#pragma once
#include "CoreMinimal.h"
#include "EEndChocoboCaptureVolumeType.generated.h"

UENUM(BlueprintType)
enum class EEndChocoboCaptureVolumeType : uint8 {
    Bush,
    Goal,
    EscapeArea,
    Sleep,
    CheckPoint,
    BalloonArea,
    BegWatching,
    NoThrowBarrier,
};

