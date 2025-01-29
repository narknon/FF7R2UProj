#pragma once
#include "CoreMinimal.h"
#include "EEndBattleSceneCountLifeCycleType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleSceneCountLifeCycleType : uint8 {
    eNone,
    eCountUp,
    eCountDown,
};

