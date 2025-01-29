#pragma once
#include "CoreMinimal.h"
#include "EEndChocoboRaceRunTrigger.generated.h"

UENUM(BlueprintType)
enum class EEndChocoboRaceRunTrigger : uint8 {
    RaceStart,
    FinalLap,
    Damage,
    ReturnCourse,
    Overtake,
    IsOvertaken,
    OverGoal,
    ForceMoveFoward,
    KeepDashDuration,
    PreDriftRequestInput,
    DisableIK,
    Max,
};

