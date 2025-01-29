#pragma once
#include "CoreMinimal.h"
#include "EEndSystemPauseMenuKind.generated.h"

UENUM(BlueprintType)
enum class EEndSystemPauseMenuKind : uint8 {
    None,
    Simple,
    CinemaPause,
    BattlePause,
    MainMenu,
    MapJournal,
    Libra,
    GameOver,
    Colosseum,
    OnlyResumeGame,
    Max,
};

