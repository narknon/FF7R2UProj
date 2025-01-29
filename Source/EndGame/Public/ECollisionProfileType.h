#pragma once
#include "CoreMinimal.h"
#include "ECollisionProfileType.generated.h"

UENUM(BlueprintType)
enum class ECollisionProfileType : uint8 {
    Wall,
    Pc_Wall,
    Party_Wall,
    NPC_Wall,
    Enemy_Wall,
    NPCEnemy_Wall,
    PC_Party_Wall,
    Speacial_Wall,
    NoCollision,
    Max,
};

