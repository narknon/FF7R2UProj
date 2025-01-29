#pragma once
#include "CoreMinimal.h"
#include "EEndBattleCameraPriorityType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleCameraPriorityType : uint8 {
    None,
    SyncAction = 10,
    Player = 20,
    Enemy = 30,
    Burst = 40,
    Summon = 50,
    ChangePhase = 60,
    Menu = 70,
    Debug,
    MAX,
};

