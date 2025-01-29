#pragma once
#include "CoreMinimal.h"
#include "EGameTrigger.generated.h"

UENUM(BlueprintType)
enum class EGameTrigger : uint8 {
    EGameTrigger_NONE,
    EGameTrigger_BOOT,
    EGameTrigger_EDITOR_BOOT,
    EGameTrigger_DEBUG_BOOT,
    EGameTrigger_TITLE,
    EGameTrigger_INIT_PERSISTENT,
    EGameTrigger_EDITOR_INIT_PERSISTENT,
    EGameTrigger_GAME_IDLE,
    EGameTrigger_PAUSE,
    EGameTrigger_PAUSE_END,
    EGameTrigger_MENU,
    EGameTrigger_MENU_END,
    EGameTrigger_UNINIT_PERSISTENT,
    EGameTrigger_PAUSE_STARTCHAPTER,
};

