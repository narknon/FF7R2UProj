#include "EndAnimNotifyStateStealCamera.h"

UEndAnimNotifyStateStealCamera::UEndAnimNotifyStateStealCamera() {
    this->bIsToStayBetweenLeaderAndSelf = false;
    this->LeaderToSelfCameraCenterRatio = 0.50f;
    this->BlendInOption = EAlphaBlendOption::Linear;
    this->BlendInTime = 0.00f;
    this->BlendOutOption = EAlphaBlendOption::Linear;
    this->BlendOutTime = 0.00f;
}


