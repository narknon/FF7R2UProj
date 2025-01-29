#pragma once
#include "CoreMinimal.h"
#include "EEndAIEnemyCautionPhase.generated.h"

UENUM(BlueprintType)
enum class EEndAIEnemyCautionPhase : uint8 {
    None,
    WaitFieldAnimation,
    PlayCautionAnimation,
    Move,
};

