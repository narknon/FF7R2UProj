#pragma once
#include "CoreMinimal.h"
#include "EEndBattleSyncActionEndType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleSyncActionEndType : uint8 {
    None,
    Escape,
    FinalAttack,
    Max,
};

