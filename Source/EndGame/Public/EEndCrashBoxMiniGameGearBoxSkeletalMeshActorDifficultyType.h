#pragma once
#include "CoreMinimal.h"
#include "EEndCrashBoxMiniGameGearBoxSkeletalMeshActorDifficultyType.generated.h"

UENUM(BlueprintType)
enum class EEndCrashBoxMiniGameGearBoxSkeletalMeshActorDifficultyType : uint8 {
    ALL,
    NORMAL_ONLY,
    HARD_ONLY,
    MAX,
};

