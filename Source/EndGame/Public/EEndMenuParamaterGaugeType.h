#pragma once
#include "CoreMinimal.h"
#include "EEndMenuParamaterGaugeType.generated.h"

UENUM(BlueprintType)
enum class EEndMenuParamaterGaugeType : uint8 {
    GaugeHP,
    GaugeHP2,
    GaugeHP3,
    GaugeMP,
    GaugeLIMIT,
    GaugeENEMY,
    GaugeMax,
};

