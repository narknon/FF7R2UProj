#include "EndShootingCoasterSpawnerTriggerBox.h"

AEndShootingCoasterSpawnerTriggerBox::AEndShootingCoasterSpawnerTriggerBox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bPrioritySpawner = false;
    this->RailActorReference = NULL;
    this->bDefaultActiveState = true;
    this->MaxLength = 0.00f;
    this->AtLength = 0.00f;
}


