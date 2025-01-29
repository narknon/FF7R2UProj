#pragma once
#include "CoreMinimal.h"
#include "EEndAnimBehaviorMatchingType.generated.h"

UENUM(BlueprintType)
enum class EEndAnimBehaviorMatchingType : uint8 {
    DeltaLocalSpaceRotationMax,
    DeltaLocalSpaceRotationAvg,
    DeltaLocalSpaceTranslationMax,
    DeltaLocalSpaceTranslationAvg,
};

