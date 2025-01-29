#pragma once
#include "CoreMinimal.h"
#include "EEndAIComboHitCondition.generated.h"

UENUM(BlueprintType)
enum class EEndAIComboHitCondition : uint8 {
    Unconditionally,
    HitToNext,
    HitToNotNext,
    MissToNext,
    GuardToNotNext,
    Max,
};

