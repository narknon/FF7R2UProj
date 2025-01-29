#pragma once
#include "CoreMinimal.h"
#include "EEndTerminalVelocityLayer.generated.h"

UENUM(BlueprintType)
enum class EEndTerminalVelocityLayer : uint8 {
    Battle,
    BattleAbility,
    Animation,
    Debug,
    Max,
};

