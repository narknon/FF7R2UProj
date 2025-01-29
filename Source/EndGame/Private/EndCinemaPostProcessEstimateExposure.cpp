#include "EndCinemaPostProcessEstimateExposure.h"

AEndCinemaPostProcessEstimateExposure::AEndCinemaPostProcessEstimateExposure(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->EnabledActivated = false;
    this->Activated = false;
    this->EnabledVariance = false;
    this->Variance = 0.00f;
    this->EnabledWeight = false;
    this->Weight = 0.00f;
}


