#pragma once
#include "CoreMinimal.h"
#include "EEndInterestPointReactionActorType.generated.h"

UENUM(BlueprintType)
enum class EEndInterestPointReactionActorType : uint8 {
    Player,
    Party,
    Npc,
    Animal,
    Type_Max UMETA(Hidden),
};

