#pragma once
#include "CoreMinimal.h"
#include "EMooglePanicTriggerType.generated.h"

UENUM(BlueprintType)
enum class EMooglePanicTriggerType : uint8 {
    MPT_Panic,
    MPT_Warp,
};

