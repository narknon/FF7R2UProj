#pragma once
#include "CoreMinimal.h"
#include "EEndChocoboRaceChocoboType.generated.h"

UENUM(BlueprintType)
enum class EEndChocoboRaceChocoboType : uint8 {
    Normal,
    MountainAndRiver,
    Sand,
    Forest,
    Sky,
    Sea,
    Mechanical,
    UniqueRival,
    Max,
};

