#pragma once
#include "CoreMinimal.h"
#include "EEndAIEnemyTargetSelectCharacterType.generated.h"

UENUM(BlueprintType)
enum class EEndAIEnemyTargetSelectCharacterType : uint8 {
    UCPC,
    AIPC,
    ALL,
    Max,
};

