#pragma once
#include "CoreMinimal.h"
#include "EVfxLightParameterFlags.generated.h"

UENUM(BlueprintType)
enum class EVfxLightParameterFlags : uint8 {
    None,
    RenderVolumetricFogOnly,
    BeamLight,
    DisableLowPerformance = 4,
};

