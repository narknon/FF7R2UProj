#include "EndStealCameraParam.h"

FEndStealCameraParam::FEndStealCameraParam() {
    this->bIsToStayBetweenLeaderAndSelf = false;
    this->LeaderToSelfCameraCenterRatio = 0.00f;
    this->Character = NULL;
    this->Alpha = 0.00f;
    this->bIsTargetStateActive = false;
}

