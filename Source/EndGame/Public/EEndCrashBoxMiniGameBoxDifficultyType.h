#pragma once
#include "CoreMinimal.h"
#include "EEndCrashBoxMiniGameBoxDifficultyType.generated.h"

UENUM(BlueprintType)
enum class EEndCrashBoxMiniGameBoxDifficultyType : uint8 {
    ALL,
    NORMAL_ONLY,
    HARD_ONLY,
    MAX,
};

