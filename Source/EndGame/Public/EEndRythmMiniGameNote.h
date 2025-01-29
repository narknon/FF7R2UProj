#pragma once
#include "CoreMinimal.h"
#include "EEndRythmMiniGameNote.generated.h"

UENUM(BlueprintType)
namespace EEndRythmMiniGameNote {
    enum Type {
        SINGLE_TAP,
        LONG_TAP,
        CONSECUTIVE_TAP,
    };
}

