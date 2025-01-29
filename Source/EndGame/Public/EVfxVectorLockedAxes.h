#pragma once
#include "CoreMinimal.h"
#include "EVfxVectorLockedAxes.generated.h"

UENUM(BlueprintType)
enum class EVfxVectorLockedAxes : uint8 {
    None,
    XYZ,
    XY,
    XZ,
    YZ,
};

