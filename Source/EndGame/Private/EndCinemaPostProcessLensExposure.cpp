#include "EndCinemaPostProcessLensExposure.h"

AEndCinemaPostProcessLensExposure::AEndCinemaPostProcessLensExposure(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->EnabledExposureBias = false;
    this->ExposureBias = 0.00f;
    this->EnabledWeight = false;
    this->Weight = 0.00f;
}


