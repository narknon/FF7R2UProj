#pragma once
#include "CoreMinimal.h"
#include "EMoogleGimmickTargetType.generated.h"

UENUM(BlueprintType)
enum class EMoogleGimmickTargetType : uint8 {
    None,
    Player,
    Moogle,
    All,
    Max,
};

