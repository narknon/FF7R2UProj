#pragma once
#include "CoreMinimal.h"
#include "ECameraInfoParamType.generated.h"

UENUM()
enum class ECameraInfoParamType : uint8 {
    Location = 1,
    Rotation,
    FOV = 4,
    SweepCenterLocation = 8,
    AimLocation = 16,
    AimDistance = 32,
    LocalAimOffset = 64,
    Height = 128,
};

