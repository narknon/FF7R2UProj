#pragma once
#include "CoreMinimal.h"
#include "EDoorActiveEffectType.generated.h"

UENUM(BlueprintType)
enum class EDoorActiveEffectType : uint8 {
    ActiveNone,
    ActiveLeft,
    ActiveRight,
    ActiveBath,
};

