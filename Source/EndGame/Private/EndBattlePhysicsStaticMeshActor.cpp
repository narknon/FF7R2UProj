#include "EndBattlePhysicsStaticMeshActor.h"
#include "EndBattleDamageSourceCollisionComponent.h"

AEndBattlePhysicsStaticMeshActor::AEndBattlePhysicsStaticMeshActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->DamageSourceCollision = CreateDefaultSubobject<UEndBattleDamageSourceCollisionComponent>(TEXT("DamageSourceCollision"));
}


