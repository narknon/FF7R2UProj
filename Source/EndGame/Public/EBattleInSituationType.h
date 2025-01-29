#pragma once
#include "CoreMinimal.h"
#include "EBattleInSituationType.generated.h"

UENUM(BlueprintType)
enum class EBattleInSituationType : uint8 {
    eNone,
    eTakeAttack,
    eSense,
    eLink,
};

