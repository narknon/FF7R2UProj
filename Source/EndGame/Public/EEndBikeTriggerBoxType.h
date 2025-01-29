#pragma once
#include "CoreMinimal.h"
#include "EEndBikeTriggerBoxType.generated.h"

UENUM(BlueprintType)
enum class EEndBikeTriggerBoxType : uint8 {
    Destroy,
    BreakBridgeKeepVelocity,
    BreakBridgePrepare,
    BreakBridgeExecute,
    BreakBridgeReset,
};

