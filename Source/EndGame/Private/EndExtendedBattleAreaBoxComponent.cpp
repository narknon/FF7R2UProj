#include "EndExtendedBattleAreaBoxComponent.h"
#include "EndNavAreaExtendedBattle.h"

UEndExtendedBattleAreaBoxComponent::UEndExtendedBattleAreaBoxComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AreaClass = UEndNavAreaExtendedBattle::StaticClass();
}


