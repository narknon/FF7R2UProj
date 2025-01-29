#pragma once
#include "CoreMinimal.h"
#include "EAIPCTargetAvailableStatus.generated.h"

UENUM(BlueprintType)
enum class EAIPCTargetAvailableStatus : uint8 {
    Available,
    Sleep,
    DefenceStatus,
    FarDefenceActor,
    NotifyInhibitAttack,
    NotBattleState,
};

