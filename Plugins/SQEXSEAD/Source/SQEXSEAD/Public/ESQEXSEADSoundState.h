#pragma once
#include "CoreMinimal.h"
#include "ESQEXSEADSoundState.generated.h"

UENUM(BlueprintType)
enum class ESQEXSEADSoundState : uint8 {
    Invalid,
    Ready,
    Playing,
    Paused,
    Unknown,
};

