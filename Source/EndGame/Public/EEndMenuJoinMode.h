#pragma once
#include "CoreMinimal.h"
#include "EEndMenuJoinMode.generated.h"

UENUM(BlueprintType)
enum class EEndMenuJoinMode : uint8 {
    NewJoin,
    ReJoin,
    LeftOut,
    Reserve,
};

