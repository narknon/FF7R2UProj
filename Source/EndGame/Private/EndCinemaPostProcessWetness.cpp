#include "EndCinemaPostProcessWetness.h"

AEndCinemaPostProcessWetness::AEndCinemaPostProcessWetness(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->EnabledActivated = false;
    this->Activated = false;
    this->EnabledRippleIntensity = false;
    this->RippleIntensity = 0.00f;
    this->EnabledTrickleIntensity = false;
    this->TrickleIntensity = 0.00f;
    this->EnabledWeight = false;
    this->Weight = 0.00f;
}


