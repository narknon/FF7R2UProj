#pragma once
#include "CoreMinimal.h"
#include "EActorType.generated.h"

UENUM(BlueprintType)
enum class EActorType : uint8 {
    EActorType_PLAYER,
    EActorType_PARTY,
    EActorType_GUEST,
    EActorType_NPC,
    EActorType_ENEMY,
    EActorType_OBJECT,
    EActorType_GUEST_Battle,
    EActorType_WEAPON,
    EActorType_RESERVE,
    EActorType_PLAYER_VEHICLE,
    EActorType_PARTY_VEHICLE,
};

