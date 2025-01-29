#pragma once
#include "CoreMinimal.h"
#include "EEndAiMoveType.generated.h"

UENUM(BlueprintType)
enum class EEndAiMoveType : uint8 {
    RUN,
    DASH,
    WALK,
    HIGHWALK,
    JOG,
    MAX,
};

