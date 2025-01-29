#include "EndWorldShiftVolume.h"

AEndWorldShiftVolume::AEndWorldShiftVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bColored = true;
    this->UntouchMargin = 5000.00f;
    this->NextPendingTime = 2.00f;
    this->bDisabled = false;
}


