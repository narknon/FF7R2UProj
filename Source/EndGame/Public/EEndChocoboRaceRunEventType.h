#pragma once
#include "CoreMinimal.h"
#include "EEndChocoboRaceRunEventType.generated.h"

UENUM(BlueprintType)
enum class EEndChocoboRaceRunEventType : uint8 {
    None,
    Glide,
    DriftL,
    DriftR,
    DisableBackCamera,
    StraightCourse,
    EnableAero,
};

