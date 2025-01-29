#pragma once
#include "CoreMinimal.h"
#include "EGameSpeed.generated.h"

UENUM(BlueprintType)
enum class EGameSpeed : uint8 {
    EGameSpeed_BATTLE_COMMAND,
    EGameSpeed_BATTLE_PARTY_CHANGE,
    EGameSpeed_BATTLE_CAMERA,
    EGameSpeed_BATTLE_HIT,
    EGameSpeed_BATTLE_HIT_COMBINATION,
    EGameSpeed_BATTLE_BURST,
    EGameSpeed_MINIGAME,
    EGameSpeed_SKIP_CINEMA,
    EGameSpeed_NOTIFY,
    EGameSpeed_FAST_FORWARD,
    EGameSpeed_CUT_DEBUG,
    EGameSpeed_DEBUG,
};

