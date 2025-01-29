#pragma once
#include "CoreMinimal.h"
#include "EEndAnimBehaviorMode.generated.h"

UENUM(BlueprintType)
enum class EEndAnimBehaviorMode : uint8 {
    Neutral,
    Battle,
    Caution,
    Max,
};

