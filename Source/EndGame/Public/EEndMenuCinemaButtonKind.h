#pragma once
#include "CoreMinimal.h"
#include "EEndMenuCinemaButtonKind.generated.h"

UENUM(BlueprintType)
enum class EEndMenuCinemaButtonKind : uint8 {
    EventSkip,
    MainMenu,
    FastForward,
};

