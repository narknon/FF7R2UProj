#pragma once
#include "CoreMinimal.h"
#include "EEndBehaviorJumpExtraActionInput.generated.h"

UENUM(BlueprintType)
enum class EEndBehaviorJumpExtraActionInput : uint8 {
    Normal,
    Fall,
    Target,
};

