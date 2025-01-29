#pragma once
#include "CoreMinimal.h"
#include "EEndSituationActionType.generated.h"

UENUM(BlueprintType)
enum class EEndSituationActionType : uint8 {
    None,
    BoxFitDirection,
    PointFitLocationDirection,
};

