#pragma once
#include "CoreMinimal.h"
#include "EEndBattleSupportFieldType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleSupportFieldType : uint8 {
    MagicSequence,
    ATBDistribute,
    CastMagic,
    CreateDamageSource,
    CactusMission,
    Max,
};

