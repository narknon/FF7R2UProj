#pragma once
#include "CoreMinimal.h"
#include "EEndLovelessPlayMiniGameKey.generated.h"

UENUM(BlueprintType)
namespace EEndLovelessPlayMiniGameKey {
    enum Type {
        SINGLE_TAP,
        CONSECUTIVE_TAP,
        ALL_BUTTONS_TAP,
    };
}

