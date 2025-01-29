#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAITargetLockGroupPriority.generated.h"

UENUM(BlueprintType)
enum class EEndBattleAITargetLockGroupPriority : uint8 {
    Low,
    Middle,
    High,
};

