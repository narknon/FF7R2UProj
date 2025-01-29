#pragma once
#include "CoreMinimal.h"
#include "BattleModeStep.generated.h"

UENUM(BlueprintType)
enum class BattleModeStep : uint8 {
    Normal,
    Warning,
    ToAggressive,
    Aggressive,
    Escaping,
    EscapingWait,
    ExitBattleSceneWait,
    BattleModeStep_StepMax,
};

