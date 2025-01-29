#pragma once
#include "CoreMinimal.h"
#include "EEndRythmMiniGameInputKey.generated.h"

UENUM(BlueprintType)
namespace EEndRythmMiniGameInputKey {
    enum Type {
        NONE = -1,
        CIRCLE = 0,
        TRIANGLE,
        SQUARE,
        CROSS,
    };
}

