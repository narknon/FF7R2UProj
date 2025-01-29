#pragma once
#include "CoreMinimal.h"
#include "EEndAnimNotifyPlayerChocoboMessageType.generated.h"

UENUM(BlueprintType)
enum class EEndAnimNotifyPlayerChocoboMessageType : uint8 {
    None,
    GlideJumpRisingCancel,
    MAX,
};

