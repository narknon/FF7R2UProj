#pragma once
#include "CoreMinimal.h"
#include "EEndAIControllerMask.generated.h"

UENUM(BlueprintType)
enum class EEndAIControllerMask : uint8 {
    SYSTEM,
    BATTLE_SUMMON,
    BATTLE_STATUS,
    SUMMON_CUTSCENE_SKILL,
    BATTLE_SYSTEM,
    AUTO_PLAY,
    BATTLE_SCENE_BP,
    BATTLE_SYNC_ACTION,
    CHARA_POP,
    WAVE,
    BATTLE_SPECIAL_STATUS,
    BATTLE_ENCOUNT,
    WAIT_WIN_MOTION,
    ANIMATION_BUDGET,
    MAX,
};

