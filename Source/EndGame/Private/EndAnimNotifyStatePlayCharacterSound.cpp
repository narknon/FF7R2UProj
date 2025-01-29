#include "EndAnimNotifyStatePlayCharacterSound.h"

UEndAnimNotifyStatePlayCharacterSound::UEndAnimNotifyStatePlayCharacterSound() {
    this->bAutoSE = false;
    this->bDedicatedAction = false;
    this->DedicatedActionSound = NULL;
    this->DedicatedActionOnEndSound = NULL;
    this->bOverrideFieldActionTargetSound = false;
}


