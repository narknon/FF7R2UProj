#pragma once
#include "CoreMinimal.h"
#include "EAIPCBattleParamType.generated.h"

UENUM(BlueprintType)
enum class EAIPCBattleParamType : uint8 {
    Normal,
    TargetBurst,
    AutoAbility,
    OrderedVehicle,
    KeepOffensiveMode,
    DodgeAttack,
    Toad,
};

