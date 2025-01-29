#include "EndCinemaPostProcessDirLightModifier.h"

AEndCinemaPostProcessDirLightModifier::AEndCinemaPostProcessDirLightModifier(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->EnabledModifier = false;
    this->Modifier = 0.00f;
    this->EnabledWeight = false;
    this->Weight = 0.00f;
}


