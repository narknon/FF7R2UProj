#pragma once
#include "CoreMinimal.h"
#include "EEndAIEnemyCautionMoveKind.generated.h"

UENUM(BlueprintType)
enum class EEndAIEnemyCautionMoveKind : uint8 {
    None,
    Approach,
    Escape,
    Keep,
    Around,
};

