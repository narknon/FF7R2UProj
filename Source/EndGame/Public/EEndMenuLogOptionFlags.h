#pragma once
#include "CoreMinimal.h"
#include "EEndMenuLogOptionFlags.generated.h"

UENUM(BlueprintType)
enum class EEndMenuLogOptionFlags : uint8 {
    None,
    Unique,
    InventoryFull,
};

