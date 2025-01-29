#pragma once
#include "CoreMinimal.h"
#include "EForceParkourCheckType.generated.h"

UENUM(BlueprintType)
enum class EForceParkourCheckType : uint8 {
    Default,
    MoveBlockOrDefault,
    MoveBlock,
    AreaAndDir,
    Area,
    MAX,
};

