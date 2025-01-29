#pragma once
#include "CoreMinimal.h"
#include "EEndCameraCustomSuspensionType.generated.h"

UENUM(BlueprintType)
enum class EEndCameraCustomSuspensionType : uint8 {
    EEndCameraCustomSuspension_Default,
    EEndCameraCustomSuspension_SoftLevel1,
    EEndCameraCustomSuspension_SoftLevel2,
    EEndCameraCustomSuspension_SoftLevel3,
    EEndCameraCustomSuspension_SlopeSoftLevel1,
    EEndCameraCustomSuspension_SlopeSoftLevel2,
    EEndCameraCustomSuspension_SlopeSoftLevel3,
};

