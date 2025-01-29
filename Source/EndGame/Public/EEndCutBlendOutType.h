#pragma once
#include "CoreMinimal.h"
#include "EEndCutBlendOutType.generated.h"

UENUM(BlueprintType)
enum class EEndCutBlendOutType : uint8 {
    None,
    NoBlend,
    SpecifiedTime,
    WaitUntilInput,
    Inertia,
};

