#pragma once
#include "CoreMinimal.h"
#include "EEndActionReportType.generated.h"

UENUM(BlueprintType)
enum class EEndActionReportType : uint8 {
    ChangeCameraParameter,
    LifeStreamerLiveAmountMax,
    ExistChocoboCustomMenu,
    RefreshActionOverrideStateSleeper,
    ColosseumResultTipsID,
    EverySnap2nd,
    FinishActionTutorial,
};

