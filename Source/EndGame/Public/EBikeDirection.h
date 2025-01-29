#pragma once
#include "CoreMinimal.h"
#include "EBikeDirection.generated.h"

UENUM(BlueprintType)
enum class EBikeDirection : uint8 {
    None,
    Front,
    Right,
    Left,
    Back,
    Max,
};

