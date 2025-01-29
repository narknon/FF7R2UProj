#pragma once
#include "CoreMinimal.h"
#include "EEndAIDistanceType.generated.h"

UENUM(BlueprintType)
enum class EEndAIDistanceType : uint8 {
    Dist2D,
    Dist3D,
    DistZ,
    DistZ_Relative,
};

