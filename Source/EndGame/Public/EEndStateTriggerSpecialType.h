#pragma once
#include "CoreMinimal.h"
#include "EEndStateTriggerSpecialType.generated.h"

UENUM(BlueprintType)
enum class EEndStateTriggerSpecialType : uint8 {
    None,
    EnvironmentAnimationLastFrame,
    IgnoreDelay,
    IgnoreSe,
    CanDelay,
};

