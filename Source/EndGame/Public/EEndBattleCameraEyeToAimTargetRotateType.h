#pragma once
#include "CoreMinimal.h"
#include "EEndBattleCameraEyeToAimTargetRotateType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleCameraEyeToAimTargetRotateType : uint8 {
    AlwaysRotate,
    FixWithRootRotate,
    FixWithoutRotate,
};

