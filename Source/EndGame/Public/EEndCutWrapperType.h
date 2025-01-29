#pragma once
#include "CoreMinimal.h"
#include "EEndCutWrapperType.generated.h"

UENUM(BlueprintType)
enum class EEndCutWrapperType : uint8 {
    Event,
    Live,
    Movie,
    MovieMonitor,
    Type_Max UMETA(Hidden),
};

