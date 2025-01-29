#pragma once
#include "CoreMinimal.h"
#include "EForcedTickMask.generated.h"

UENUM(BlueprintType)
enum class EForcedTickMask : uint8 {
    EForcedTickMask_CINEMA,
    EForcedTickMask_ANIMATION,
    EForcedTickMask_DIALOGUE,
    EForcedTickMask_MINIGAME,
    EForcedTickMask_FIELDACTION,
    EForcedTickMask_DEBUG,
};

