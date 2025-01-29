#include "EndShootingCoasterEventTriggerBox.h"

AEndShootingCoasterEventTriggerBox::AEndShootingCoasterEventTriggerBox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RailActorReference = NULL;
    this->bDefaultActiveState = true;
    this->MaxLength = 0.00f;
    this->AtLength = 0.00f;
}


