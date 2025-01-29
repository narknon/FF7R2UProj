#pragma once
#include "CoreMinimal.h"
#include "EEndAIBattlePhaseChangeActionIdType.generated.h"

UENUM(BlueprintType)
enum class EEndAIBattlePhaseChangeActionIdType : uint8 {
    ReactionId,
    AbilityId,
};

