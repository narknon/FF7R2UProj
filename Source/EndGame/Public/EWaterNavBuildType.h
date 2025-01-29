#pragma once
#include "CoreMinimal.h"
#include "EWaterNavBuildType.generated.h"

UENUM(BlueprintType)
enum class EWaterNavBuildType : uint8 {
    None,
    Hollow,
    Ignore,
};

