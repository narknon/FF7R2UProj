#pragma once
#include "CoreMinimal.h"
#include "EEquipType.generated.h"

UENUM(BlueprintType)
enum class EEquipType : uint8 {
    Weapon,
    Bangle,
    Accessory,
    Max,
};

