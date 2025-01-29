#pragma once
#include "CoreMinimal.h"
#include "EEndMenuGamepadType.generated.h"

UENUM(BlueprintType)
enum class EEndMenuGamepadType : uint8 {
    Default,
    XInput,
    DirectInput,
};

