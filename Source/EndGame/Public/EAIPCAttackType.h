#pragma once
#include "CoreMinimal.h"
#include "EAIPCAttackType.generated.h"

UENUM(BlueprintType)
enum class EAIPCAttackType : uint8 {
    eCombo,
    eContinuous,
    eNone,
};

