#pragma once
#include "CoreMinimal.h"
#include "BattleStep.generated.h"

UENUM(BlueprintType)
enum class BattleStep : uint8 {
    NormalStep,
    EscapingStep,
    WarningStep,
    AggressiveStep,
    BattleModeStepMax,
};

