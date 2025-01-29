#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAIDangerAreaType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleAIDangerAreaType : uint8 {
    eNone,
    eCircle,
    eRectangle,
};

