#pragma once
#include "CoreMinimal.h"
#include "EOptionSelectionKind.generated.h"

UENUM(BlueprintType)
enum class EOptionSelectionKind : uint8 {
    List,
    Range,
    Gamepad,
    Keyboard,
};

