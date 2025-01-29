#pragma once
#include "CoreMinimal.h"
#include "EEndAIEnemyCancel.generated.h"

UENUM(BlueprintType)
enum class EEndAIEnemyCancel : uint8 {
    None,
    Turn,
    ReactionAvoid,
    FastDash,
    Max,
};

