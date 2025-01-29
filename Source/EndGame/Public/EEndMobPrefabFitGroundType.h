#pragma once
#include "CoreMinimal.h"
#include "EEndMobPrefabFitGroundType.generated.h"

UENUM(BlueprintType)
enum class EEndMobPrefabFitGroundType : uint8 {
    FitGroundAndIK,
    FitGroundOnly,
    NoFitGround,
    Ocean,
    Max,
};

