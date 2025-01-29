#pragma once
#include "CoreMinimal.h"
#include "EEndEmotionalGesture.generated.h"

UENUM(BlueprintType)
enum class EEndEmotionalGesture : uint8 {
    None,
    LookAround,
    Warning,
};

