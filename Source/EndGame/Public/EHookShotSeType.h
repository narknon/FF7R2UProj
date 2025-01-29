#pragma once
#include "CoreMinimal.h"
#include "EHookShotSeType.generated.h"

UENUM(BlueprintType)
enum class EHookShotSeType : uint8 {
    Concrete,
    IronPlate,
    SteelFrame,
};

