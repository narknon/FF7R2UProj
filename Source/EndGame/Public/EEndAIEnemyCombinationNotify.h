#pragma once
#include "CoreMinimal.h"
#include "EEndAIEnemyCombinationNotify.generated.h"

UENUM(BlueprintType)
enum class EEndAIEnemyCombinationNotify : uint8 {
    None,
    FirstAction,
    ExecuteAction,
    AfterMove,
    Special,
    Max,
};

