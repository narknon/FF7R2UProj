#pragma once
#include "CoreMinimal.h"
#include "EEndCrashBoxMiniGameGearBoxDifficultyType.generated.h"

UENUM(BlueprintType)
enum class EEndCrashBoxMiniGameGearBoxDifficultyType : uint8 {
    ALL,
    NORMAL_ONLY,
    HARD_ONLY,
    MAX,
};

