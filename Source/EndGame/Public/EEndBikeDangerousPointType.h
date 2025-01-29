#pragma once
#include "CoreMinimal.h"
#include "EEndBikeDangerousPointType.generated.h"

UENUM(BlueprintType)
enum class EEndBikeDangerousPointType : uint8 {
    None,
    DamageSource,
    AnimNotify,
    LockOnMarker,
};

