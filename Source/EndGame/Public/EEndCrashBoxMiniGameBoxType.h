#pragma once
#include "CoreMinimal.h"
#include "EEndCrashBoxMiniGameBoxType.generated.h"

UENUM(BlueprintType)
enum class EEndCrashBoxMiniGameBoxType : uint8 {
    NORMAL,
    ABILITY,
    ABILITY2,
    HIGH_GREAD,
    ELECTRIC,
    HIGH_GREAD_L,
    ELECTRIC_L,
    PHYSICAL,
    MAGIC,
    STOP,
    CACTUS,
    CACTUS_L,
    GEAR,
    MAX,
};

