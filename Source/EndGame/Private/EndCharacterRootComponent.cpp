#include "EndCharacterRootComponent.h"

UEndCharacterRootComponent::UEndCharacterRootComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bIgnoreDodgeRoll = false;
    this->bIgnoreAttackTargetAsTarget = false;
    this->bIgnoreAttackTargetAsAttacker = false;
}


