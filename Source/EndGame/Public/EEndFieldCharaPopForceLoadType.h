#pragma once
#include "CoreMinimal.h"
#include "EEndFieldCharaPopForceLoadType.generated.h"

UENUM(BlueprintType)
enum class EEndFieldCharaPopForceLoadType : uint8 {
    Limit500,
    Limit3000,
    Limit4000,
    Max,
};

