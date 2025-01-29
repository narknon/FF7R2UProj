#pragma once
#include "CoreMinimal.h"
#include "EEndAnimalRunFloatParameterType.generated.h"

UENUM(BlueprintType)
enum class EEndAnimalRunFloatParameterType : uint8 {
    CommonShootPower,
    CommonShootPowerVert,
    AttackBaseShootDistance,
    AttackBaseShootDiffAngle,
    AttackBaseRestTimeAfterShoot,
    AttackerRestTime,
    AttackerRestTimeMax,
    AttackerChasingTime,
    AttackerChasingTimeMax,
    AttackerStopChaseDisntace,
    StrikerRangeMin,
    StrikerRangeMax,
    GoalKeeperSearchRangeRadius,
    GoalKeeperRestTime,
    GoalKeeperRestTimeMax,
    GoalKeeperMoveRangeRadius,
    GoalKeeperRestTimeAfterShoot,
    AnchorRangeMin,
    AnchorRangeMax,
};

