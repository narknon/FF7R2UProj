#pragma once
#include "CoreMinimal.h"
#include "EEndAIReactionPlayerType.generated.h"

UENUM(BlueprintType)
enum class EEndAIReactionPlayerType : uint8 {
    All,
    UCPC,
    AIPC,
    Max,
};

