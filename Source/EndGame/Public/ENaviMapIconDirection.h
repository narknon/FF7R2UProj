#pragma once
#include "CoreMinimal.h"
#include "ENaviMapIconDirection.generated.h"

UENUM(BlueprintType)
enum class ENaviMapIconDirection : uint8 {
    None,
    North,
    NorthEast,
    East,
    SouthEast,
    South,
    SouthWest,
    West,
    NorthWest,
};

