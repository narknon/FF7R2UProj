#pragma once
#include "CoreMinimal.h"
#include "EEndAIEnemyPointSelectType.generated.h"

UENUM(BlueprintType)
enum class EEndAIEnemyPointSelectType : uint8 {
    DistanceMin,
    DistanceMax,
    Direction,
    Max,
};

