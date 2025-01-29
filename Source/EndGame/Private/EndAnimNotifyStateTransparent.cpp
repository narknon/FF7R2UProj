#include "EndAnimNotifyStateTransparent.h"

UEndAnimNotifyStateTransparent::UEndAnimNotifyStateTransparent() {
    this->FadeType = EEndAnimNotifyDitherFadeType::Default;
    this->TurnTransparentTime = 0.20f;
    this->TurnOpaqueTime = 0.20f;
}


