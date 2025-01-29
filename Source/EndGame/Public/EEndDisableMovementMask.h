#pragma once
#include "CoreMinimal.h"
#include "EEndDisableMovementMask.generated.h"

UENUM(BlueprintType)
enum class EEndDisableMovementMask : uint8 {
    Loading,
    WarpInLocation,
    FastTravel,
    Interrupt,
    AttributeChanger,
    WaitingCollision,
    MiniGame,
    FieldManager,
    Debug,
    Max,
};

