#include "EndBattleAreaBoxComponent.h"
#include "EndNavAreaBattle.h"

UEndBattleAreaBoxComponent::UEndBattleAreaBoxComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AreaClass = UEndNavAreaBattle::StaticClass();
}


