#pragma once
#include "CoreMinimal.h"
#include "EDataBaseEquipmentObtainmentStatus.generated.h"

UENUM(BlueprintType)
enum class EDataBaseEquipmentObtainmentStatus : uint8 {
    Undiscovered,
    Obtained,
    Displayed,
};

