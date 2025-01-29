#pragma once
#include "CoreMinimal.h"
#include "EEndExtensionAIStateFieldAction.generated.h"

UENUM(BlueprintType)
enum class EEndExtensionAIStateFieldAction : uint8 {
    NONE,
    LADDER,
    CRACK_MOVE,
    CROUCHED,
    CHOCOBO_CLIMB,
};

