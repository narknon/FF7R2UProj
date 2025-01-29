#include "EndAnimNotifyStatePlaySound.h"

UEndAnimNotifyStatePlaySound::UEndAnimNotifyStatePlaySound() {
    this->StartWaitTime = 0.00f;
    this->VolumeMultiplier = 1.00f;
    this->PitchMultiplier = 1.00f;
    this->FadeOutDuration = 0.00f;
    this->bFollow = true;
    this->Attenuation = NULL;
    this->bPauseOnAnimKeep = true;
    this->bVirtualizePlayWhenSilent = false;
    this->bSyncOwnerHiddenState = true;
}


