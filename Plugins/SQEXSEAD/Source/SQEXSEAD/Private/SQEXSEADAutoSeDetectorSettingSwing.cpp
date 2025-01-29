#include "SQEXSEADAutoSeDetectorSettingSwing.h"

FSQEXSEADAutoSeDetectorSettingSwing::FSQEXSEADAutoSeDetectorSettingSwing() {
    this->bOverrideKnockParameters = false;
    this->KnockDetectVelocityThreshold = 0.00f;
    this->KnockVolumeRangeMin = 0.00f;
    this->KnockVolumeRangeMax = 0.00f;
    this->bOverrideRubParameters = false;
    this->RubDetectVelocityThreshold = 0.00f;
    this->RubVolumeRangeMin = 0.00f;
    this->RubVolumeRangeMax = 0.00f;
}

