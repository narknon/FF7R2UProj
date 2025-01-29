#pragma once
#include "CoreMinimal.h"
#include "EEndAIBTScreenLogType.generated.h"

UENUM(BlueprintType)
enum class EEndAIBTScreenLogType : uint8 {
    Standard,
    Warning,
    Error,
};

