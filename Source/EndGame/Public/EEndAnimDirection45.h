#pragma once
#include "CoreMinimal.h"
#include "EEndAnimDirection45.generated.h"

UENUM(BlueprintType)
enum class EEndAnimDirection45 : uint8 {
    Forward,
    Left_45,
    Left_90,
    Left_135,
    Left_180,
    Right_45,
    Right_90,
    Right_135,
    Right_180,
};

