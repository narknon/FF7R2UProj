#pragma once
#include "CoreMinimal.h"
#include "EEndMenuTalkSelectWindowType.generated.h"

UENUM(BlueprintType)
enum class EEndMenuTalkSelectWindowType : uint8 {
    center,
    left,
    CenterList = center,
    LeftList = left,
    Directional,
};

