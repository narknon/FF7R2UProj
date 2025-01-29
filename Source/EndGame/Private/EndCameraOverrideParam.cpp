#include "EndCameraOverrideParam.h"

FEndCameraOverrideParam::FEndCameraOverrideParam() {
    this->bOverrideFOV = false;
    this->OverrideFOV = 0.00f;
    this->bAddDistance = false;
    this->AddDistance = 0.00f;
    this->bAddAimHeight = false;
    this->AddAimHeight = 0.00f;
    this->bOverrideRotation = false;
    this->bOverrideFollowSpeed = false;
    this->OverrideFollowSpeed = 0.00f;
    this->bOverrideAimOffsetY = false;
    this->OverrideAimOffsetY = 0.00f;
}

