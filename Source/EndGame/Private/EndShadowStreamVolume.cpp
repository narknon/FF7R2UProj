#include "EndShadowStreamVolume.h"

AEndShadowStreamVolume::AEndShadowStreamVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bColored = true;
    this->StaticShadowForward = 50000.00f;
    this->StaticShadowBack = 0.00f;
    this->UntouchMargin = 0.00f;
    this->Priority = 128;
    this->bDisabled = false;
}


