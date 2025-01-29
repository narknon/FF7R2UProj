#pragma once
#include "CoreMinimal.h"
#include "EDebugMessageShowType.generated.h"

UENUM(BlueprintType)
enum class EDebugMessageShowType : uint8 {
    None,
    Window,
    Log,
    ScreenLog,
};

