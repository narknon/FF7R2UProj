#pragma once
#include "CoreMinimal.h"
#include "EBikeMothSlasherAttackType.generated.h"

UENUM(BlueprintType)
enum class EBikeMothSlasherAttackType : uint8 {
    None,
    Default,
    Charge,
    Discharge,
    Phase2,
};

