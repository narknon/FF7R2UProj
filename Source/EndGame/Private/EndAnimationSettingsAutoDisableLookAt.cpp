#include "EndAnimationSettingsAutoDisableLookAt.h"

FEndAnimationSettingsAutoDisableLookAt::FEndAnimationSettingsAutoDisableLookAt() {
    this->OverrideHeadBaseAngleThreshold = 0.00f;
    this->DisableAngleThreshold = 0.00f;
    this->DisableAngularVelocityThreshold = 0.00f;
    this->DisableAngularVelocityThresholdApplyAngleOffset = 0.00f;
    this->InputFrameOffset = 0;
    this->DuringFrameMin = 0;
}

