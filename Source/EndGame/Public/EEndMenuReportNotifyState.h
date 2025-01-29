#pragma once
#include "CoreMinimal.h"
#include "EEndMenuReportNotifyState.generated.h"

UENUM(BlueprintType)
enum class EEndMenuReportNotifyState : uint8 {
    None,
    Added,
    Completed,
    Notice,
    CompletedNow,
    FoundLocation,
};

