#include "AnimNotify_EndCoordinateAnimationRange.h"

UAnimNotify_EndCoordinateAnimationRange::UAnimNotify_EndCoordinateAnimationRange() {
    this->Curve = EEndAnimationCurveType::OneLoop;
    this->Duration = 1.00f;
    this->bCallStopOnEnd = true;
}


