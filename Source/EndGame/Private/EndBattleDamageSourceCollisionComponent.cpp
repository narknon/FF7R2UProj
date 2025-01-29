#include "EndBattleDamageSourceCollisionComponent.h"

UEndBattleDamageSourceCollisionComponent::UEndBattleDamageSourceCollisionComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bAutoActivate = true;
    this->CatchGroupNumber = -1;
    this->bStartWithHidden = false;
    this->bIgnorePlayerDamageSource = false;
    this->OwnerActor = NULL;
    this->PossessionActor = NULL;
}


