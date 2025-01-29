#pragma once
#include "CoreMinimal.h"
#include "EForceUpdateAnimationCategory.generated.h"

UENUM(BlueprintType)
enum class EForceUpdateAnimationCategory : uint8 {
    MiniGame,
    FieldExtraAction,
    AI,
    AIOverlap,
    WildAnimal,
    Battle,
    Vehicle,
    StateChange,
    Cinema,
    Action,
};

