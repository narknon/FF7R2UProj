#include "EndDialogueSequenceBlendOutSetting.h"

FEndDialogueSequenceBlendOutSetting::FEndDialogueSequenceBlendOutSetting() {
    this->BlendTime = 0.00f;
    this->BlendStartTime = 0.00f;
    this->BlendOption = EAlphaBlendOption::Linear;
    this->bSetFieldCameraDirection = false;
}

