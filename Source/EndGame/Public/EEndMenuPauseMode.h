#pragma once
#include "CoreMinimal.h"
#include "EEndMenuPauseMode.generated.h"

UENUM(BlueprintType)
enum class EEndMenuPauseMode : uint8 {
    Normal,
    Simple,
    Cinema,
    CinemaNoSkip,
    Battle,
    MapJournal,
    Colosseum,
    ColosseumResult,
    Libra,
    CommandHelp,
    MiniGamePause,
    PcUpgrade,
};

