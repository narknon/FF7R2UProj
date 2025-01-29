#include "EndCinemaCoordinateAnimParams.h"

FEndCinemaCoordinateAnimParams::FEndCinemaCoordinateAnimParams() {
    this->Curve = EEndAnimationCurveType::ZeroLoop;
    this->Duration = 0.00f;
    this->bCallStopOnEnd = false;
}

