#pragma once
#include "CoreMinimal.h"
#include "EEndFieldActionMessageType.generated.h"

UENUM(BlueprintType)
enum class EEndFieldActionMessageType : uint8 {
    None,
    DropRedHoldItem,
    CloudSuppressEnd,
    WarpInVolumeCart,
    PollingLifeStormAreaCtrl,
    ResetCable,
    Max,
};

