#include "EndCinemaSceneLightCurveSection.h"

UEndCinemaSceneLightCurveSection::UEndCinemaSceneLightCurveSection() {
    this->PropertyCurve = NULL;
    this->PlayMode = EEndCinemaSceneLightCurvePlayType::NoLoop;
    this->ApplyMode = EEndCinemaSceneLightCurveApplyType::Multiplication;
    this->CurveScaling = 1.00f;
}


