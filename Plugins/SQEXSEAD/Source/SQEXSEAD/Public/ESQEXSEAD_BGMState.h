#pragma once
#include "CoreMinimal.h"
#include "ESQEXSEAD_BGMState.generated.h"

UENUM(BlueprintType)
enum class ESQEXSEAD_BGMState : uint8 {
    Invalid,
    NotReady,
    Ready,
    AutoPlay,
    Playing,
    Stop,
    Suspended,
    AutoResume,
};

