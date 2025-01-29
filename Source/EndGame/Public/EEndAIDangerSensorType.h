#pragma once
#include "CoreMinimal.h"
#include "EEndAIDangerSensorType.generated.h"

UENUM(BlueprintType)
enum class EEndAIDangerSensorType : uint8 {
    InDamageArea,
    InDamageAreaSensor,
    NearDamageArea,
    InDodgeAreaTarget,
};

