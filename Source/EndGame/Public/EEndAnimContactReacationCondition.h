#pragma once
#include "CoreMinimal.h"
#include "EEndAnimContactReacationCondition.generated.h"

UENUM(BlueprintType)
enum class EEndAnimContactReacationCondition : uint8 {
    Default,
    AllowedPlayingMobPrefab,
    AllowedPlayingMobPrefabAndExtraAction,
    Max,
};

