#pragma once
#include "CoreMinimal.h"
#include "EEndBikeNextActionType.generated.h"

UENUM(BlueprintType)
enum class EEndBikeNextActionType : uint8 {
    None,
    Move,
    Ability,
    Ability_ATB,
    Accel,
    Brake,
};

