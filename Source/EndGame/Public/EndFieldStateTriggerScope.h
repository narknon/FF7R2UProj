#pragma once
#include "CoreMinimal.h"
#include "EndFieldStateTriggerScope.generated.h"

UENUM(BlueprintType)
enum class EndFieldStateTriggerScope : uint8 {
    EndFieldStateTriggerScope_Self,
    EndFieldStateTriggerScope_Location,
    EndFieldStateTriggerScope_ResidentAndLocation,
    EndFieldStateTriggerScope_SpecificObject,
};

