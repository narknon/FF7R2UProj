#pragma once
#include "CoreMinimal.h"
#include "ESQEX_KD_ConnectionType.generated.h"

UENUM(BlueprintType)
enum class ESQEX_KD_ConnectionType : uint8 {
    ESQEX_KD_ConnectionType_Float,
    ESQEX_KD_ConnectionType_Vector3,
    ESQEX_KD_ConnectionType_Quaternion,
};

