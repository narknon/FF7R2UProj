#pragma once
#include "CoreMinimal.h"
#include "EChocoboType.generated.h"

UENUM(BlueprintType)
enum class EChocoboType : uint8 {
    Normal,
    MountainAndRiver,
    Sand,
    Forest,
    Sky,
    Sea,
    Secret,
    Max,
};

