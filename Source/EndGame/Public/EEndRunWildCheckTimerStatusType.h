#pragma once
#include "CoreMinimal.h"
#include "EEndRunWildCheckTimerStatusType.generated.h"

UENUM(BlueprintType)
enum class EEndRunWildCheckTimerStatusType : uint8 {
    IsRunning,
    IsFinished,
};

