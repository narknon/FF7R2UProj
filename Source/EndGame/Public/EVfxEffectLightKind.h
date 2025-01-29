#pragma once
#include "CoreMinimal.h"
#include "EVfxEffectLightKind.generated.h"

UENUM()
enum class EVfxEffectLightKind : int32 {
    Ambiguous,
    Punctual,
    Max,
    Unpunctual = Ambiguous,
};

