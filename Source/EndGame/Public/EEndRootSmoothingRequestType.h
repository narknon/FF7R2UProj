#pragma once
#include "CoreMinimal.h"
#include "EEndRootSmoothingRequestType.generated.h"

UENUM(BlueprintType)
enum class EEndRootSmoothingRequestType : uint8 {
    Animation,
    Move,
    Action,
    Field,
    Battle,
    WalkingMob,
    Debug,
};

