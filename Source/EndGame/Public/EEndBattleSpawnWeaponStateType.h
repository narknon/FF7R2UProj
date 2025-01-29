#pragma once
#include "CoreMinimal.h"
#include "EEndBattleSpawnWeaponStateType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleSpawnWeaponStateType : uint8 {
    None,
    Create,
    Finish,
    CreateRockThrow,
    HaveRockThrow,
    ThrowRockThrow,
    BrokenRockThrow,
    DisappearRockThrow,
    CreateGraniteJail,
    StartGraniteJail,
    CompletedGraniteJail,
    FailureGraniteJail,
    CancelGraniteJail,
    CreateChargeCrystal,
    SummonChargeCrystal,
    BrokenChargeCrystal,
};

