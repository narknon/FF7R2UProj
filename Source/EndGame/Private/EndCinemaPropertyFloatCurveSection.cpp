#include "EndCinemaPropertyFloatCurveSection.h"

UEndCinemaPropertyFloatCurveSection::UEndCinemaPropertyFloatCurveSection() {
    this->bSupportsInfiniteRange = true;
    this->PropertyCurve = NULL;
    this->PlayMode = EEndCinemaPropertyCurvePlayType::NoLoop;
    this->ApplyMode = EEndCinemaPropertyCurveApplyType::Multiplication;
    this->CurveScaling = 1.00f;
}


