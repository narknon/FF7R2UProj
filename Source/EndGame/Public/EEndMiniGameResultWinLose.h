#pragma once
#include "CoreMinimal.h"
#include "EEndMiniGameResultWinLose.generated.h"

UENUM(BlueprintType)
enum class EEndMiniGameResultWinLose : uint8 {
    None,
    Win,
    Lose,
    Draw,
};

