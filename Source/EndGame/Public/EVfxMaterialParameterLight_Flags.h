#pragma once
#include "CoreMinimal.h"
#include "EVfxMaterialParameterLight_Flags.generated.h"

UENUM(BlueprintType)
enum class EVfxMaterialParameterLight_Flags : uint8 {
    None,
    ExposureCondition,
    Default = ExposureCondition,
};

