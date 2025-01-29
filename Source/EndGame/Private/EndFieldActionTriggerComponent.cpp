#include "EndFieldActionTriggerComponent.h"

UEndFieldActionTriggerComponent::UEndFieldActionTriggerComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->ActionType = EFieldActionActorType::None;
    this->CustomParam = NULL;
}


