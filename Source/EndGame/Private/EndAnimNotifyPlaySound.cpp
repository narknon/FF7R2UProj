#include "EndAnimNotifyPlaySound.h"

UEndAnimNotifyPlaySound::UEndAnimNotifyPlaySound() {
    this->VolumeMultiplier = 1.00f;
    this->PitchMultiplier = 1.00f;
    this->bFollow = true;
    this->Attenuation = NULL;
    this->bSyncOwnerHiddenState = true;
    this->bUsePadSpeaker = false;
}


