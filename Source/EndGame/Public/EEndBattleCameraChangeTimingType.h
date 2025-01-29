#pragma once
#include "CoreMinimal.h"
#include "EEndBattleCameraChangeTimingType.generated.h"

UENUM(BlueprintType)
enum class EEndBattleCameraChangeTimingType : uint8 {
    None,
    DamageSourceGenerated,
    DamageSourceHit,
    Branch0,
    Branch1,
    SummonSpawned,
    ActorNameDamageSourceHit,
    MAX,
};

