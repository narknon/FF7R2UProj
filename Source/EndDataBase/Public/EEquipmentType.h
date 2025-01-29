#pragma once
#include "CoreMinimal.h"
#include "EEquipmentType.generated.h"

UENUM(BlueprintType)
enum class EEquipmentType : uint8 {
    EEquipmentType_PLAYER,
    EEquipmentType_WEAPON,
};

