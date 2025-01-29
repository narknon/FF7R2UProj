#include "EndAIInterestActionMoveTo.h"

FEndAIInterestActionMoveTo::FEndAIInterestActionMoveTo() {
    this->StopTolerance = 0.00f;
    this->bInterpolationMove = false;
    this->MoveType = EEndAiMoveType::RUN;
    this->PathType = EFieldAiPathWayType::None;
    this->bCanOutSideMove = false;
}

