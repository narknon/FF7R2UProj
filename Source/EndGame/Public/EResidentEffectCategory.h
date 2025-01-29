#pragma once
#include "CoreMinimal.h"
#include "EResidentEffectCategory.generated.h"

UENUM(BlueprintType)
enum class EResidentEffectCategory : uint8 {
    Default,
    MoveMode,
    Notify,
    CutScene,
    EndPlay,
};

