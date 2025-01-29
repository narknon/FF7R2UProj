#pragma once
#include "CoreMinimal.h"
#include "EndBattleMode.generated.h"

UENUM(BlueprintType)
enum class EndBattleMode : uint8 {
    EndBattleMode_Normal,
    EndBattleMode_Warning,
    EndBattleMode_Aggressive,
};

