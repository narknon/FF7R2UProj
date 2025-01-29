#pragma once
#include "CoreMinimal.h"
#include "EEndWaterType.generated.h"

UENUM(BlueprintType)
enum class EEndWaterType : uint8 {
    Default,
    Swamp,
    River,
    Ocean,
    SandSwamp,
};

