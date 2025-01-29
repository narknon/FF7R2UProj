#pragma once
#include "CoreMinimal.h"
#include "LineType.generated.h"

UENUM(BlueprintType)
enum class LineType : uint8 {
    Center,
    Right,
    Left,
};

