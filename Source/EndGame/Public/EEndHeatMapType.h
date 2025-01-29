#pragma once
#include "CoreMinimal.h"
#include "EEndHeatMapType.generated.h"

UENUM()
enum class EEndHeatMapType : int32 {
    ENEMY,
    PLAYER,
    MAX,
};

