#pragma once
#include "CoreMinimal.h"
#include "EEndCameraLookAtDeactivateType.generated.h"

UENUM(BlueprintType)
enum class EEndCameraLookAtDeactivateType : uint8 {
    ReturnPitch,
    KeepPitch,
    ResetPitch,
};

