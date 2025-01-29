#pragma once
#include "CoreMinimal.h"
#include "EEndAIEnemyTargetSelectConditionType.generated.h"

UENUM(BlueprintType)
enum class EEndAIEnemyTargetSelectConditionType : uint8 {
    None,
    HPPerHigh,
    HPPerLow,
    DistanceNear,
    DistanceFar,
    SyncAction,
    Stun,
    StatusChangeEffect = 50,
    Sleep = 66,
    SpecialStatusChange = 100,
    Restraint = 141,
    Max,
};

