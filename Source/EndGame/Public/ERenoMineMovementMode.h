#pragma once
#include "CoreMinimal.h"
#include "ERenoMineMovementMode.generated.h"

UENUM(BlueprintType)
enum class ERenoMineMovementMode : uint8 {
    NONE,
    Spawning,
    Prowl,
    Prowl_1Mines,
    Prowl_2Mines,
    Prowl_3Mines,
    Prowl_4Mines,
    Prowl_5Mines,
    Prowl_6Mines,
    Prowl_7Mines,
    Prowl_8Mines,
    Prowl_9Mines,
    Prowl_10Mines,
    RollAroundTornado,
    RollAround_SpecialAttack,
    DestroyedOutsideOfField,
    Destroyed,
};

