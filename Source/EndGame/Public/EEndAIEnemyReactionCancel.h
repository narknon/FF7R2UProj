#pragma once
#include "CoreMinimal.h"
#include "EEndAIEnemyReactionCancel.generated.h"

UENUM(BlueprintType)
enum class EEndAIEnemyReactionCancel : uint8 {
    None,
    Counter,
    Guard,
    Avoid,
    Max,
};

