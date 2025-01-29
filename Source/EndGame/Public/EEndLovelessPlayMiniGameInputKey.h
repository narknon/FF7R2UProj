#pragma once
#include "CoreMinimal.h"
#include "EEndLovelessPlayMiniGameInputKey.generated.h"

UENUM(BlueprintType)
namespace EEndLovelessPlayMiniGameInputKey {
    enum Type {
        NONE = -1,
        CIRCLE = 0,
        TRIANGLE,
        SQUARE,
        CROSS,
        R1,
    };
}

