#pragma once
#include "CoreMinimal.h"
#include "EGameState.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8 {
    EGameState_NONE,
    EGameState_BOOT,
    EGameState_EDITOR_BOOT,
    EGameState_DEBUG_BOOT,
    EGameState_TITLE,
    EGameState_INIT_PERSISTENT,
    EGameState_GAME_IDLE,
    EGameState_PAUSE_IDLE,
    EGameState_MENU_IDLE,
    EGameState_UNINIT_PERSISTENT,
    EGameState_PAUSE_IDLE_STARTCHAPTER,
    EGameState_MAX = 32 UMETA(Hidden),
};

