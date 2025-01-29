#include "EndFieldClimbingJumpPointSetting.h"

FEndFieldClimbingJumpPointSetting::FEndFieldClimbingJumpPointSetting() {
    this->JumpPointType = EClimbingJumpPointType::ToClimbing;
    this->HookRopeActor = NULL;
    this->ClimbingActor = NULL;
    this->ClimbingPointIndex = 0;
}

