#pragma once
#include "CoreMinimal.h"
#include "EAutoDoorActiveEffectType.generated.h"

UENUM(BlueprintType)
enum class EAutoDoorActiveEffectType : uint8 {
    AutoDoorActiveNone,
    AutoDoorActiveLeft,
    AutoDoorActiveRight,
    AutoDoorActiveBoth,
};

