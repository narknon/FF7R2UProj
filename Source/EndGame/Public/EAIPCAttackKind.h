#pragma once
#include "CoreMinimal.h"
#include "EAIPCAttackKind.generated.h"

UENUM(BlueprintType)
enum class EAIPCAttackKind : uint8 {
    ShortRange,
    LongRange,
    YuffieWithoutShuriken,
};

