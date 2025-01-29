#pragma once
#include "CoreMinimal.h"
#include "EEndStreamingSwitchType.generated.h"

UENUM(BlueprintType)
enum class EEndStreamingSwitchType : uint8 {
    Simple,
    Seamless,
    Preload,
    SwitchToPreloaded,
    ForceSwitch,
};

