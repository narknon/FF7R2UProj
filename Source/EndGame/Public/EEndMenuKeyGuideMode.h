#pragma once
#include "CoreMinimal.h"
#include "EEndMenuKeyGuideMode.generated.h"

UENUM(BlueprintType)
enum class EEndMenuKeyGuideMode : uint8 {
    Gamepad,
    Keyboard,
    Gamepad_XInput,
    Gamepad_DirectInput,
};

