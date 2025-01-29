#include "AnimNotify_EndCoordinateAnimation.h"

UAnimNotify_EndCoordinateAnimation::UAnimNotify_EndCoordinateAnimation() {
    this->Curve = EEndAnimationCurveType::OneLoop;
    this->bLoop = false;
    this->Duration = 1.00f;
}


