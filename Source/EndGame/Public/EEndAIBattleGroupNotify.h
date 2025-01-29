#pragma once
#include "CoreMinimal.h"
#include "EEndAIBattleGroupNotify.generated.h"

UENUM(BlueprintType)
enum class EEndAIBattleGroupNotify : uint8 {
    PartyAll,
    Party,
    Leader,
    Individual,
    Max,
};

