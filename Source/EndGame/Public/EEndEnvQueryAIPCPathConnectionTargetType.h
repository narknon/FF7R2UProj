#pragma once
#include "CoreMinimal.h"
#include "EEndEnvQueryAIPCPathConnectionTargetType.generated.h"

UENUM(BlueprintType)
enum class EEndEnvQueryAIPCPathConnectionTargetType : uint8 {
    BattleTarget,
    CombinationTarget,
};

