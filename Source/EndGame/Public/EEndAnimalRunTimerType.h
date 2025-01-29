#pragma once
#include "CoreMinimal.h"
#include "EEndAnimalRunTimerType.generated.h"

UENUM(BlueprintType)
enum class EEndAnimalRunTimerType : uint8 {
    Rest,
    Chase,
    AfterShoot,
    Max,
};

