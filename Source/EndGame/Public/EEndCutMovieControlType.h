#pragma once
#include "CoreMinimal.h"
#include "EEndCutMovieControlType.generated.h"

UENUM(BlueprintType)
enum class EEndCutMovieControlType : uint8 {
    Stop,
    Play,
    LoopPlay,
    Open,
};

