#pragma once
#include "CoreMinimal.h"
#include "EEndChocoboRaceRunType.generated.h"

UENUM(BlueprintType)
enum class EEndChocoboRaceRunType : uint8 {
    Constant,
    First,
    Stay,
    LastSpurt,
    Random,
    Max,
};

