#pragma once
#include "CoreMinimal.h"
#include "EEndAISensorDangerObjectType.generated.h"

UENUM(BlueprintType)
enum class EEndAISensorDangerObjectType : uint8 {
    DangerDamage,
    DangerArea,
};

