#pragma once
#include "CoreMinimal.h"
#include "EEndLookAtWeightModifierType.generated.h"

UENUM(BlueprintType)
enum class EEndLookAtWeightModifierType : uint8 {
    Notify,
    AnimSet,
    Debug,
};

