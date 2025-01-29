#pragma once
#include "CoreMinimal.h"
#include "EEndLookAtForceDeactiveType.generated.h"

UENUM(BlueprintType)
enum class EEndLookAtForceDeactiveType : uint8 {
    Field,
    FieldAttack,
    MiniGame,
    Battle,
    BattleAbility,
    Cinema,
    Notify,
    MotionPose,
    Animation,
    AnimSet,
    Facial,
    Max,
};

