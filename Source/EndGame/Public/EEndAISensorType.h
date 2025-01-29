#pragma once
#include "CoreMinimal.h"
#include "EEndAISensorType.generated.h"

UENUM(BlueprintType)
enum class EEndAISensorType : uint8 {
    BattleEyeTrace,
    AbilityReaction,
    DangerObject,
    Interest,
    MAX,
};

