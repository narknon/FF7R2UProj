#include "EndGroupBoneSetting.h"

FEndGroupBoneSetting::FEndGroupBoneSetting() {
    this->VelocityThreshold = 0.00f;
    this->VelocityMax = 0.00f;
    this->OverrideAttenuation = NULL;
    this->OverrideConvurrency = NULL;
    this->MoveSupressionTimeSec = 0.00f;
}

