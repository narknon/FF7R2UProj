#pragma once
#include "CoreMinimal.h"
#include "EEndBikeHitFilterPartsType.generated.h"

UENUM(BlueprintType)
enum class EEndBikeHitFilterPartsType : uint8 {
    None,
    RightWheels,
    LeftWheels,
};

