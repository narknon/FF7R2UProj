#pragma once
#include "CoreMinimal.h"
#include "EEndMoveMode.generated.h"

UENUM(BlueprintType)
enum class EEndMoveMode : uint8 {
    EEndMoveMode_Default,
    EEndMoveMode_None,
    EEndMoveMode_Flying,
    EEndMoveMode_FlyingAsWalk,
};

