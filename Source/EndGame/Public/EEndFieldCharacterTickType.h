#pragma once
#include "CoreMinimal.h"
#include "EEndFieldCharacterTickType.generated.h"

UENUM(BlueprintType)
enum class EEndFieldCharacterTickType : uint8 {
    None,
    TickLight,
    TickMiddle,
    TickHeavy,
    Max,
};

