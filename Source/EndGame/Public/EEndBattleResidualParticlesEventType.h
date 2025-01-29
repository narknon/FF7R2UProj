#pragma once
#include "CoreMinimal.h"
#include "EEndBattleResidualParticlesEventType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleResidualParticlesEventType : uint8 {
    None,
    ActionToStay,
    ActionToMove,
    ActionToDisappear,
};

