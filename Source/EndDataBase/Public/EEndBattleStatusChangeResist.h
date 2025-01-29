#pragma once
#include "CoreMinimal.h"
#include "EEndBattleStatusChangeResist.generated.h"

UENUM(BlueprintType)
enum class EEndBattleStatusChangeResist : uint8 {
    Poison,
    Fury,
    Sadness,
    Silence,
    Sleep,
    Slow,
    Stop,
    GradualPetrify,
    Berserk,
    Frog,
    DeathSentence,
    Deprotect,
    Deshell,
    Debrave,
    Defaith,
    Petrify,
    Max,
    None = Max,
};

