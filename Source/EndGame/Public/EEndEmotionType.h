#pragma once
#include "CoreMinimal.h"
#include "EEndEmotionType.generated.h"

UENUM(BlueprintType)
enum class EEndEmotionType : uint8 {
    Unknown,
    Calm,
    Anger,
    Joy,
    Sorrow,
};

