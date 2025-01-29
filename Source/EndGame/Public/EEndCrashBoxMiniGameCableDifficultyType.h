#pragma once
#include "CoreMinimal.h"
#include "EEndCrashBoxMiniGameCableDifficultyType.generated.h"

UENUM(BlueprintType)
enum class EEndCrashBoxMiniGameCableDifficultyType : uint8 {
    ALL,
    NORMAL_ONLY,
    HARD_ONLY,
    MAX,
};

