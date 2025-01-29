#include "EndDialogueGenerateSourceShot.h"

FEndDialogueGenerateSourceShot::FEndDialogueGenerateSourceShot() {
    this->ShotAssetIndex = 0;
    this->bLoopShot = false;
    this->bEndShot = false;
    this->bEnableShotSkip = false;
    this->bDisableShotSkipOnSkipCinema = false;
    this->bUnbindCamera = false;
    this->bFixCharacterTransform = false;
    this->bFixCharacterLookAt = false;
    this->bFixConstraint = false;
    this->bDisableLookAt = false;
    this->CharacterLookAtType = EEndDialogueGenerateSourceLookAtType::ForceEnable;
    this->bEnableCameraShake = false;
    this->bOverrideCameraInCharacterNames = false;
    this->ShotType = EEndDialogueGenerateSourceShotType::Near;
    this->bReverseShot = false;
}

