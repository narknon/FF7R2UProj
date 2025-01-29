#include "EndBattleBreakableComponent.h"

UEndBattleBreakableComponent::UEndBattleBreakableComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bAutoActivate = true;
    this->bStartWithHidden = false;
    this->OwnerActor = NULL;
}


