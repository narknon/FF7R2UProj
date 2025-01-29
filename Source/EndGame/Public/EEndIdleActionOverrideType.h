#pragma once
#include "CoreMinimal.h"
#include "EEndIdleActionOverrideType.generated.h"

UENUM(BlueprintType)
enum class EEndIdleActionOverrideType : uint8 {
    AIState,
    Interest,
    WildAnimal,
    Debug,
    Max,
};

