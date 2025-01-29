#pragma once
#include "CoreMinimal.h"
#include "EndBattleExitBattleSceneType.generated.h"

UENUM(BlueprintType)
enum class EndBattleExitBattleSceneType : uint8 {
    EndBattleMode_Finish,
    EndBattleMode_Escape,
    EndBattleMode_Leave,
};

