#pragma once
#include "CoreMinimal.h"
#include "EEndWalkModeModifierType.generated.h"

UENUM(BlueprintType)
enum class EEndWalkModeModifierType : uint8 {
    Controller,
    Battle,
    BattleGuard,
    BattleResult,
    PlannerEvent,
    WalkingMob,
    WildAnimal,
    Slope,
    FieldAction,
};

