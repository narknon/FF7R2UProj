#pragma once
#include "CoreMinimal.h"
#include "EEndCutPhysicsMode.generated.h"

UENUM(BlueprintType)
enum class EEndCutPhysicsMode : uint8 {
    Standard,
    Continuous,
    Disable,
};

