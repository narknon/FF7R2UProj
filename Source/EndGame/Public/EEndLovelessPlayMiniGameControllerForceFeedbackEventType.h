#pragma once
#include "CoreMinimal.h"
#include "EEndLovelessPlayMiniGameControllerForceFeedbackEventType.generated.h"

UENUM(BlueprintType)
namespace EEndLovelessPlayMiniGameControllerForceFeedbackEventType {
    enum Type {
        SINGLE_VIBRATION,
        LONG_VIBRATION_START,
        LONG_VIBRATION_END,
    };
}

