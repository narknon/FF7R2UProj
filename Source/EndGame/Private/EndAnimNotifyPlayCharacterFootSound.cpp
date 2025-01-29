#include "EndAnimNotifyPlayCharacterFootSound.h"

UEndAnimNotifyPlayCharacterFootSound::UEndAnimNotifyPlayCharacterFootSound() {
    this->AutoSeMotionType = ESQEXSEADAutoSeMotionSoundType::Walk;
    this->bDirectAssign = false;
    this->SwitchValue = 0.00f;
    this->ZeroOneSlotIndex = -1;
    this->ZeroOneValue = 0.00f;
    this->bPlayOnlyCharecterLanded = true;
    this->bSyncOwnerHiddenState = true;
}


