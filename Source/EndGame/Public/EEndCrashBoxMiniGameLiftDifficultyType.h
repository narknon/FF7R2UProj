#pragma once
#include "CoreMinimal.h"
#include "EEndCrashBoxMiniGameLiftDifficultyType.generated.h"

UENUM(BlueprintType)
enum class EEndCrashBoxMiniGameLiftDifficultyType : uint8 {
    ALL,
    NORMAL_ONLY,
    HARD_ONLY,
    MAX,
};

