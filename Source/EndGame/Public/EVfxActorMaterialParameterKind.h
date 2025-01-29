#pragma once
#include "CoreMinimal.h"
#include "EVfxActorMaterialParameterKind.generated.h"

UENUM(BlueprintType)
enum class EVfxActorMaterialParameterKind : uint8 {
    Coverage,
    Light,
    ExtraPixelCoordinate,
    ExtraNormalizedCoordinate,
    AnimateTime,
    GenericVector,
    TransitionCoverage,
};

