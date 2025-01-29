#pragma once
#include "CoreMinimal.h"
#include "EVfxTransformContextParameterFlags.generated.h"

UENUM(BlueprintType)
enum class EVfxTransformContextParameterFlags : uint8 {
    None,
    Blending,
    AnimateOnce,
};

