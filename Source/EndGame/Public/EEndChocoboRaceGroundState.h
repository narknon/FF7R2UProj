#pragma once
#include "CoreMinimal.h"
#include "EEndChocoboRaceGroundState.generated.h"

UENUM(BlueprintType)
enum class EEndChocoboRaceGroundState : uint8 {
    Normal,
    RunOffGrass,
    RunOffWater,
    Fall,
    Action,
};

