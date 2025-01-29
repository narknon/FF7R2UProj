#pragma once
#include "CoreMinimal.h"
#include "EEndAnimNotifyBuggyMessageType.generated.h"

UENUM(BlueprintType)
enum class EEndAnimNotifyBuggyMessageType : uint8 {
    None,
    AppearEventFocusCarKey,
    AppearEventRunBuggy,
    MAX,
};

