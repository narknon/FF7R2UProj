#pragma once
#include "CoreMinimal.h"
#include "EEndRootMotionModifierType.generated.h"

UENUM(BlueprintType)
enum class EEndRootMotionModifierType : uint8 {
    None,
    FieldAction,
    BattleAction,
    BattleMove,
    CharaSpec,
    Notify,
    FieldAI,
    Dash,
    MoveTo,
    Animation,
    WildAnimal,
    MiniGame,
    WalkingMob,
    Debug,
};

