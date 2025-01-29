#pragma once
#include "CoreMinimal.h"
#include "EEndDisableMovementRotationMask.generated.h"

UENUM(BlueprintType)
enum class EEndDisableMovementRotationMask : uint8 {
    FieldAction,
    Attach,
    MiniGame,
    DisableMovement,
    Cinema,
};

