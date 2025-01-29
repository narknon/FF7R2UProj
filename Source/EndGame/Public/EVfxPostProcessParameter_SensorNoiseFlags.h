#pragma once
#include "CoreMinimal.h"
#include "EVfxPostProcessParameter_SensorNoiseFlags.generated.h"

UENUM()
enum class EVfxPostProcessParameter_SensorNoiseFlags {
    None,
    EnabledActivated,
    Activated,
    EnabledVariance = 4,
    EnabledMonochrome = 16,
    Monochrome = 32,
    EnabledExposureCondition = 64,
    ExposureCondition = 128,
    EnabledFraction = 256,
    Default = 199,
};

