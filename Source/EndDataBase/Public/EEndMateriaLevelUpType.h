#pragma once
#include "CoreMinimal.h"
#include "EEndMateriaLevelUpType.generated.h"

UENUM(BlueprintType)
enum class EEndMateriaLevelUpType : uint8 {
    AP,
    ITEM,
    MAX,
};

