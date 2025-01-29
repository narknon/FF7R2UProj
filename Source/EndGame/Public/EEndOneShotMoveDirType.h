#pragma once
#include "CoreMinimal.h"
#include "EEndOneShotMoveDirType.generated.h"

UENUM(BlueprintType)
enum class EEndOneShotMoveDirType : uint8 {
    BothWays,
    RightToLeft,
    LeftToRight,
    Max,
};

