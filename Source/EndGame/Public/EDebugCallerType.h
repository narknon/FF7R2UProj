#pragma once
#include "CoreMinimal.h"
#include "EDebugCallerType.generated.h"

UENUM(BlueprintType)
enum class EDebugCallerType : uint8 {
    Action,
    Animation,
    Bike,
    Battle,
    BluePrint,
    CutScene,
    Debug,
    System,
    SelfUpdate,
    PartyMgr,
    PlannerEvent,
    Encount,
    AI,
    VehicleSystem,
    MiniGame,
    ChadleySystem,
    Colosseum,
    Movement,
};

