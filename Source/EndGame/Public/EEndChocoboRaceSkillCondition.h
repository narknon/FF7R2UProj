#pragma once
#include "CoreMinimal.h"
#include "EEndChocoboRaceSkillCondition.generated.h"

UENUM(BlueprintType)
enum class EEndChocoboRaceSkillCondition : uint8 {
    None,
    Always,
    RaceStart,
    FinalLap,
    NearGoal,
    LowerRank,
    EqualRank,
    UpperRank,
    Overtake,
    IsOvertaken,
    NearTop,
    ReturnCourse,
    Damage,
    StraightCourse,
    Slope,
    CountDown,
    RocketStart,
    Drift,
    RunOff,
    Water,
    DashFloor,
    OnMoogle,
    FinalLapState,
};

