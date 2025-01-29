#pragma once
#include "CoreMinimal.h"
#include "EEndBattleCameraRelativeLocationRotateType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleCameraRelativeLocationRotateType : uint8 {
    AlwaysRotate,
    FixWithRotate,
    FixWithoutRotate,
};

