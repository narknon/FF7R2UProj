#pragma once
#include "CoreMinimal.h"
#include "EndFieldSkipType.generated.h"

UENUM(BlueprintType)
enum class EndFieldSkipType : uint8 {
    CutScene,
    PlannerEvent,
    Other,
    None,
    MAX,
};

