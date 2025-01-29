#pragma once
#include "CoreMinimal.h"
#include "EEndCautionAnimType.generated.h"

UENUM(BlueprintType)
enum class EEndCautionAnimType : uint8 {
    AsNeutral,
    AsBattle,
    Max,
};

