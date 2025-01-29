#pragma once
#include "CoreMinimal.h"
#include "EMenuItemCategory.generated.h"

UENUM(BlueprintType)
enum class EMenuItemCategory : uint8 {
    GamePlay,
    CameraController,
    Sound,
    Language,
    Graphics,
    Gamepad,
    Keyboard,
};

