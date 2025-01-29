#pragma once
#include "CoreMinimal.h"
#include "EEndCrashBoxMiniGameBoxTypePhysics.generated.h"

UENUM(BlueprintType)
enum class EEndCrashBoxMiniGameBoxTypePhysics : uint8 {
    NORMAL,
    ABILITY,
    HIGH_GREAD,
    ELECTRIC,
    MAX,
};

