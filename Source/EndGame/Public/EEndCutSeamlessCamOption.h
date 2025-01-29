#pragma once
#include "CoreMinimal.h"
#include "EEndCutSeamlessCamOption.generated.h"

UENUM(BlueprintType)
enum class EEndCutSeamlessCamOption : uint8 {
    Default,
    LastCamTransOnCut,
    CSCO_Max UMETA(Hidden),
};

