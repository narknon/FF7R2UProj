#pragma once
#include "CoreMinimal.h"
#include "EVfxPostProcessParameter_LensFilterFlags.generated.h"

UENUM()
enum class EVfxPostProcessParameter_LensFilterFlags {
    None,
    EnabledActivated,
    Activated,
    EnabledNeutralDensity = 4,
    EnabledColorModulation = 16,
    EnabledNormalizedTint = 64,
    EnabledPhaseModulation = 256,
    Default = 7,
};

