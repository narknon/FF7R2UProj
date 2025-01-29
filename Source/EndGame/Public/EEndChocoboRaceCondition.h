#pragma once
#include "CoreMinimal.h"
#include "EEndChocoboRaceCondition.generated.h"

UENUM(BlueprintType)
enum class EEndChocoboRaceCondition : uint8 {
    VeryBad,
    Bad,
    Normal,
    Good,
    VeryGood,
};

