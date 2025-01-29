#pragma once
#include "CoreMinimal.h"
#include "EEndAILayerStatus.generated.h"

UENUM(BlueprintType)
enum class EEndAILayerStatus : uint8 {
    None,
    Active,
    Deactive,
    Suspend,
    SuspendEntry,
};

