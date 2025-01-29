#pragma once
#include "CoreMinimal.h"
#include "EEndBattleSummonTrigger.generated.h"

UENUM(BlueprintType)
enum class EEndBattleSummonTrigger : uint8 {
    BurstChance,
    Burst,
    BurstHit,
    DyingDamageTaken,
    MemberDie,
    BluePrintEvent,
    Debug,
};

