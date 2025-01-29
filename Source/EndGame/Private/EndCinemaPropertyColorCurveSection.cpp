#include "EndCinemaPropertyColorCurveSection.h"

UEndCinemaPropertyColorCurveSection::UEndCinemaPropertyColorCurveSection() {
    this->bSupportsInfiniteRange = true;
    this->PropertyCurve = NULL;
    this->PlayMode = EEndCinemaPropertyCurvePlayType::NoLoop;
    this->ApplyMode = EEndCinemaPropertyCurveApplyType::Multiplication;
    this->CurveScaling = 1.00f;
}


