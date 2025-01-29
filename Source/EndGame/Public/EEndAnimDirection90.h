#pragma once
#include "CoreMinimal.h"
#include "EEndAnimDirection90.generated.h"

UENUM(BlueprintType)
enum class EEndAnimDirection90 : uint8 {
    Forward,
    Left_90,
    Left_180,
    Right_90,
    Right_180,
};

