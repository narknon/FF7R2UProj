#include "EndFieldAddWallRunningTriggerBoxMaker.h"

UEndFieldAddWallRunningTriggerBoxMaker::UEndFieldAddWallRunningTriggerBoxMaker(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bBlockBoxOutMove = false;
    this->bSetJumpDownPoint = false;
    this->JumpDownPointPriority = 0;
}


