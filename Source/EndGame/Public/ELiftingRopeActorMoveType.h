#pragma once
#include "CoreMinimal.h"
#include "ELiftingRopeActorMoveType.generated.h"

UENUM(BlueprintType)
enum class ELiftingRopeActorMoveType : uint8 {
    UpperToLower,
    LowerToUpper,
};

