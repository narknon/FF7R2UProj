#pragma once
#include "CoreMinimal.h"
#include "EBallSpawnConditionType.generated.h"

UENUM(BlueprintType)
enum class EBallSpawnConditionType : uint8 {
    Once,
    repetition,
    Max,
};

