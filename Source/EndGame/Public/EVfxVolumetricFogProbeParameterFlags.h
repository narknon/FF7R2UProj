#pragma once
#include "CoreMinimal.h"
#include "EVfxVolumetricFogProbeParameterFlags.generated.h"

UENUM()
enum class EVfxVolumetricFogProbeParameterFlags {
    None,
    RadialBasisX,
    RadialBasisY,
    RadialBasisZ = 4,
    ExtentCornerX = 8,
    ExtentCornerY = 16,
    ExtentCornerZ = 32,
    BoxShape = 268435456,
};

