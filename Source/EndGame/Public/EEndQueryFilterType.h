#pragma once
#include "CoreMinimal.h"
#include "EEndQueryFilterType.generated.h"

UENUM(BlueprintType)
enum class EEndQueryFilterType : uint8 {
    Default,
    Battle,
    BattleCaution,
    SimpleBattle,
    NoBattle,
    Cover,
    NoCost,
    CentralWayStreet,
    RightWayStreet,
    LeftWayStreet,
    CinemaFilter,
    NoFieldAction,
    NoCinemaObstacle,
    Territory,
    TerritoryAll,
    NoWorldLink,
    IgnoreWater,
    SandSwampyLand,
    AddAttribute,
    TerritoryEncount,
    NarrowLane,
    IgnoreFieldActionLink,
    AvoidAnimal,
    IgnoreAllNavLink,
    TinyBronco,
    Custom,
    Max,
};

