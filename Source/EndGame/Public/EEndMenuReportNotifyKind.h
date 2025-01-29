#pragma once
#include "CoreMinimal.h"
#include "EEndMenuReportNotifyKind.generated.h"

UENUM(BlueprintType)
enum class EEndMenuReportNotifyKind : uint8 {
    WorldReport,
    BattleMission,
    Colosseum,
    ChadleyReport,
    Hub,
};

