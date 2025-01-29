#pragma once
#include "CoreMinimal.h"
#include "EAutoMagicTargetPriorityType.generated.h"

UENUM(BlueprintType)
enum class EAutoMagicTargetPriorityType : uint8 {
    EnemyRank,
    IsBurst,
};

