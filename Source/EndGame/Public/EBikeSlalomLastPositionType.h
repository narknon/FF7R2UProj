#pragma once
#include "CoreMinimal.h"
#include "EBikeSlalomLastPositionType.generated.h"

UENUM(BlueprintType)
enum class EBikeSlalomLastPositionType : uint8 {
    None,
    SameSideOfPlayer,
    OtherSideOfPlayer,
};

