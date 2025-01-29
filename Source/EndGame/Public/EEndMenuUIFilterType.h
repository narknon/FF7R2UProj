#pragma once
#include "CoreMinimal.h"
#include "EEndMenuUIFilterType.generated.h"

UENUM(BlueprintType)
enum class EEndMenuUIFilterType : uint8 {
    WaitMode,
    Dying,
    MainMenu,
    MainMenuParticle,
    MainMenuFade,
    MainMenuMono,
    Stone,
    FilterMax,
};

