#pragma once
#include "CoreMinimal.h"
#include "EPauseMask.generated.h"

UENUM(BlueprintType)
enum class EPauseMask : uint8 {
    EPauseMask_DEBUG,
    EPauseMask_SYSTEM,
    EPauseMask_MENUPAUSE,
    EPauseMask_HIDE_WORLD,
    EPauseMask_INIT,
    EPauseMask_LOADER,
    EPauseMask_CHARAPOP,
    EPauseMask_BATTLE,
    EPauseMask_BATTLE_SUMMON,
    EPauseMask_CINEMA,
    EPauseMask_FIELDtoCINEMA,
    EPauseMask_FIELDtoBATTLE,
    EPauseMask_FIELD,
    EPauseMask_FIELDtoAI,
    EPauseMask_EXCLUSION,
    EPauseMask_SCENE,
    EPauseMask_ANIMATION_BUDGET,
    EPauseMask_ENCOUNT,
    EPauseMask_WAVE,
    EPauseMask_MINIGAME,
    EPauseMask_LOADING,
    EPauseMask_BATTLE_BP,
    EPauseMask_WEAPON_ANIMATION,
    EPauseMask_FIELD_PRELOADANIMATION,
    EPauseMask_DIALOGUE,
    EPauseMask_VEHICLE,
    EPauseMask_PARTY,
    EPauseMask_PAUSE_ACTOR,
    EPauseMask_FIELDACTION,
};

