#pragma once
#include "CoreMinimal.h"
#include "EEndAIEnemyGuardExecSate.generated.h"

UENUM(BlueprintType)
enum class EEndAIEnemyGuardExecSate : uint8 {
    None,
    Ability,
    Animation,
    Damage,
    Max,
};

