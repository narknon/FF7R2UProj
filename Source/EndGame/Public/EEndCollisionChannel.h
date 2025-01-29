#pragma once
#include "CoreMinimal.h"
#include "EEndCollisionChannel.generated.h"

UENUM(BlueprintType)
enum EEndCollisionChannel {
    EEndCollisionChannel_WorldStatic,
    EEndCollisionChannel_WorldDynamic,
    EEndCollisionChannel_Pawn,
    EEndCollisionChannel_Visibility,
    EEndCollisionChannel_Camera,
    EEndCollisionChannel_PhysicsBody,
    EEndCollisionChannel_Vehicle,
    EEndCollisionChannel_Destructible,
    EEndCollisionChannel_Player,
    EEndCollisionChannel_Terrain,
    EEndCollisionChannel_BattleDamageHit,
    EEndCollisionChannel_Ragdoll,
    EEndCollisionChannel_Common_Trigger,
    EEndCollisionChannel_PhysicsBlock,
};

