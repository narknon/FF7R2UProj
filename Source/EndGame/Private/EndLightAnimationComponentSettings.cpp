#include "EndLightAnimationComponentSettings.h"

FEndLightAnimationComponentSettings::FEndLightAnimationComponentSettings() {
    this->bIntensityBlendInLogarithmicSpace = false;
    this->DefaultCurve = EEndAnimationCurveType::ZeroLoop;
    this->DefaultCurveAsset = NULL;
    this->bDefaultCurveEvaluateInLogarithmicSpace = false;
    this->DefaultDuration = 0.00f;
    this->DefaultRandomAdditiveDuration = 0.00f;
    this->DefaultRandomOffset = 0.00f;
}

