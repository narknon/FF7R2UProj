#pragma once
#include "CoreMinimal.h"
#include "ESQEX_BonamikTempCollisionShape.generated.h"

UENUM(BlueprintType)
enum class ESQEX_BonamikTempCollisionShape : uint8 {
    None,
    Sphere,
    Box = 8,
};

