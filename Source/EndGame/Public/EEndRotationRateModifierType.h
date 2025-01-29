#pragma once
#include "CoreMinimal.h"
#include "EEndRotationRateModifierType.generated.h"

UENUM(BlueprintType)
enum class EEndRotationRateModifierType : uint8 {
    Field,
    Action,
    WildAnimal,
    AIMove,
    AIAction,
};

