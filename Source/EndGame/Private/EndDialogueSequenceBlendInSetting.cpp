#include "EndDialogueSequenceBlendInSetting.h"

FEndDialogueSequenceBlendInSetting::FEndDialogueSequenceBlendInSetting() {
    this->BlendTime = 0.00f;
    this->BlendingWaitTime = 0.00f;
    this->BlendOption = EAlphaBlendOption::Linear;
    this->CharacterSmoothingBlendTime = 0.00f;
    this->CharacterSmoothingBlendOption = EAlphaBlendOption::Linear;
}

