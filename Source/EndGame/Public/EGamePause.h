#pragma once
#include "CoreMinimal.h"
#include "EGamePause.generated.h"

UENUM(BlueprintType)
enum class EGamePause : uint8 {
    EGamePause_SYSTEM,
    EGamePause_LEVEL,
    EGamePause_DEBUG,
    EGamePause_SUSPEND,
    EGamePause_WORLDSYSTEM,
    EGamePause_STREAMING,
    EGamePause_MINIGAME,
    EGamePause_PLANNVEREVENT,
};

