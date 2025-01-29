#include "EndCinemaPostProcessDepthOfField.h"

AEndCinemaPostProcessDepthOfField::AEndCinemaPostProcessDepthOfField(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->EnabledActivated = false;
    this->Activated = false;
    this->EnabledFocalDistance = false;
    this->FocalDistance = 0.00f;
    this->EnabledFstop = false;
    this->Fstop = 0.00f;
    this->EnabledWeight = false;
    this->Weight = 0.00f;
    this->EnabledAutoFocalDistance = true;
}


