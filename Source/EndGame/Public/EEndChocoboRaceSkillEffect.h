#pragma once
#include "CoreMinimal.h"
#include "EEndChocoboRaceSkillEffect.generated.h"

UENUM(BlueprintType)
enum class EEndChocoboRaceSkillEffect : uint8 {
    None,
    SpeedUp,
    AccelerationUp,
    WeightUp,
    CornaringUp,
    GripUp,
    IntelligenceUp,
    RocketStartRangeUp,
    RocketStartSpeedUp,
    DashSpeedUp,
    DashDurationUp,
    DashStockMaxUp,
    AddDashStock,
    AddAbilityGauge,
    DriftTurboDurationUp,
    DriftTurboSpeedUp,
    RunOffPenaltyDown,
    WaterPenaltyDown,
    AbilityEffectUp,
    DashFloorUp,
    DamagePenaltyDown,
    CourseOutPenaltyDown,
    RandomAbilitySet,
    ItemUp,
    SpeedUp_DiffTop,
};

