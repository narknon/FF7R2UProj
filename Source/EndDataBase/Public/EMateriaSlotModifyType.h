#pragma once
#include "CoreMinimal.h"
#include "EMateriaSlotModifyType.generated.h"

UENUM(BlueprintType)
enum class EMateriaSlotModifyType : uint8 {
    NONE,
    ADD,
    CONNECT,
    MAX,
};

