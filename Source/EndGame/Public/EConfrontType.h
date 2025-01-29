#pragma once
#include "CoreMinimal.h"
#include "EConfrontType.generated.h"

UENUM(BlueprintType)
enum class EConfrontType : uint8 {
    COMBAT,
    CAUTION,
    COMMAND,
    STANDBY,
    ABILITY,
    WRAPAROUND,
    COMMAND_FALLBACK,
    ABILITY_TELEPORT,
    UNIQUE,
    GUARDORDER,
    SUPPORT_COMBINATION,
};

