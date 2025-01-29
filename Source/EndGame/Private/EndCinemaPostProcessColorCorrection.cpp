#include "EndCinemaPostProcessColorCorrection.h"

AEndCinemaPostProcessColorCorrection::AEndCinemaPostProcessColorCorrection(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->EnabledColorCorrection = false;
    this->VolumeTexture = NULL;
}


