#include "EndCinemaPostProcessLensVignette.h"

AEndCinemaPostProcessLensVignette::AEndCinemaPostProcessLensVignette(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->EnabledCorrection = false;
    this->Correction = 0.00f;
    this->EnabledWeight = false;
    this->Weight = 0.00f;
}


