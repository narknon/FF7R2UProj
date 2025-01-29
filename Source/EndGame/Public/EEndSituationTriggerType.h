#pragma once
#include "CoreMinimal.h"
#include "EEndSituationTriggerType.generated.h"

UENUM(BlueprintType)
enum class EEndSituationTriggerType : uint8 {
    BoxOverlap,
    BoxOverlapDirection,
    BoxOverlapDirectionBoth,
    TargetIcon,
};

