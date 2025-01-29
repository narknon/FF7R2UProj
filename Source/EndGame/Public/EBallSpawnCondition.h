#pragma once
#include "CoreMinimal.h"
#include "EBallSpawnCondition.generated.h"

UENUM(BlueprintType)
enum class EBallSpawnCondition : uint8 {
    SpawnElapsedTime,
    StartElapsedTime,
    GoalBallIndex,
    CurrentBallCount,
    TeamAScore,
    TeamBScore,
    TeamCScore,
    TeamDScore,
    TotalScore,
    Max,
};

