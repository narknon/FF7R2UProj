#include "EndCinemaPostProcessMotionBlur.h"

AEndCinemaPostProcessMotionBlur::AEndCinemaPostProcessMotionBlur(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->EnabledShutter = false;
    this->Shutter = 0.00f;
    this->EnabledLimitation = false;
    this->Limitation = 0.00f;
    this->EnabledWeight = false;
    this->Weight = 0.00f;
}


