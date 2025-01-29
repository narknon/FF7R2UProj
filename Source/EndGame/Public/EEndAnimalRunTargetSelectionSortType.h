#pragma once
#include "CoreMinimal.h"
#include "EEndAnimalRunTargetSelectionSortType.generated.h"

UENUM(BlueprintType)
enum class EEndAnimalRunTargetSelectionSortType : uint8 {
    Score,
    DistanceFromBall,
    Player,
    FirstPlacePlayer,
    CurrentTarget,
    AllyTarget,
    Max,
};

