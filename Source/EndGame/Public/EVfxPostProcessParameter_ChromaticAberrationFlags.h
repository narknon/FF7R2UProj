#pragma once
#include "CoreMinimal.h"
#include "EVfxPostProcessParameter_ChromaticAberrationFlags.generated.h"

UENUM(BlueprintType)
enum class EVfxPostProcessParameter_ChromaticAberrationFlags : uint8 {
    None,
    EnabledActivated,
    Activated,
    EnabledVariance = 4,
    Default = 7,
};

