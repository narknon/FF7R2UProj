#pragma once
#include "CoreMinimal.h"
#include "EVfxNonUniformKind.generated.h"

UENUM(BlueprintType)
enum class EVfxNonUniformKind : uint8 {
    None,
    Linear,
    Multiply,
    MultiplyAverage,
    ArcSin,
};

