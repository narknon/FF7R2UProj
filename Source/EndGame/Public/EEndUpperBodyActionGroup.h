#pragma once
#include "CoreMinimal.h"
#include "EEndUpperBodyActionGroup.generated.h"

UENUM(BlueprintType)
enum class EEndUpperBodyActionGroup : uint8 {
    Default,
    LeftHand,
    RightHand,
    Max,
};

