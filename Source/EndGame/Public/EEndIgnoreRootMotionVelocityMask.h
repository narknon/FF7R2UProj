#pragma once
#include "CoreMinimal.h"
#include "EEndIgnoreRootMotionVelocityMask.generated.h"

UENUM(BlueprintType)
enum class EEndIgnoreRootMotionVelocityMask : uint8 {
    FieldAction,
    Attach,
    MiniGame,
};

