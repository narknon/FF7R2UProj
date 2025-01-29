#pragma once
#include "CoreMinimal.h"
#include "EEndAIIntervalType.generated.h"

UENUM(BlueprintType)
enum class EEndAIIntervalType : uint8 {
    LightAttack,
    HardAttack,
    ExtraInterval,
    Max,
    None,
};

