#include "FindJumpArrivalStepHeightInfo.h"

FFindJumpArrivalStepHeightInfo::FFindJumpArrivalStepHeightInfo() {
    this->UpHeightMax = 0.00f;
    this->UpDistanceMax = 0.00f;
    this->UpStartToPlayerDistanceMax = 0.00f;
    this->bUpStopMove = false;
    this->bUpJumpButton = false;
    this->bUpAutoClimbingCatch = false;
    this->bUpAutoDodgeToJump = false;
    this->UpStopReactionType = EEndFieldNaviEdgeStopReactionType::None;
    this->DownHeightMin = 0.00f;
    this->DownDistanceMax = 0.00f;
    this->AddDownDistanceMax = 0.00f;
    this->DownStartToPlayerDistanceMax = 0.00f;
    this->bDownStopMove = false;
    this->bDownJumpButton = false;
    this->bDownAutoClimbingCatch = false;
    this->bDownAutoDodgeToJump = false;
    this->DownStopReactionType = EEndFieldNaviEdgeStopReactionType::None;
}

