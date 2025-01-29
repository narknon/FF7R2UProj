#pragma once
#include "CoreMinimal.h"
#include "EEndMenuScrollBarPosition.generated.h"

UENUM(BlueprintType)
enum class EEndMenuScrollBarPosition : uint8 {
    None,
    RightOrBottom,
    LeftOrTop,
};

