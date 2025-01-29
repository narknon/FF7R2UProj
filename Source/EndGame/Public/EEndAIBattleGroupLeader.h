#pragma once
#include "CoreMinimal.h"
#include "EEndAIBattleGroupLeader.generated.h"

UENUM(BlueprintType)
enum class EEndAIBattleGroupLeader : uint8 {
    None,
    CanLeader,
    Leader,
    Max,
};

