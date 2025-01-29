#include "EndNavWheelieBlockWallVolume.h"

AEndNavWheelieBlockWallVolume::AEndNavWheelieBlockWallVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bPC_Wall = false;
    this->bParty_Wall = false;
    this->bSubParty_Wall = false;
    this->bNPC_Wall = false;
    this->bEnemy_Wall = false;
    this->TriggerInterval = 1.00f;
}


