#pragma once
#include "CoreMinimal.h"
#include "EEndAnimDisableUpdateCondition.generated.h"

UENUM(BlueprintType)
enum class EEndAnimDisableUpdateCondition : uint8 {
    None,
    NoAnimation,
    Always,
};

